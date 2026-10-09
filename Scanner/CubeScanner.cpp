#include "CubeScanner.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace cv;
using namespace std;

// Static color map definition
// Static color map definition with high contrast between Red and Orange
const map<RubbixCube::Color, Scalar> CubeScanner::colorMap = {
    {RubbixCube::Color::White,  Scalar(255, 255, 255)},
    {RubbixCube::Color::Red,    Scalar(0, 0, 240)},      // Vivid Crimson Red
    {RubbixCube::Color::Orange, Scalar(0, 130, 255)},    // Bright Warm Orange
    {RubbixCube::Color::Yellow, Scalar(0, 235, 235)},
    {RubbixCube::Color::Green,  Scalar(0, 200, 0)},
    {RubbixCube::Color::Blue,   Scalar(220, 50, 0)}
};

CubeScanner::CubeScanner(int camIndex, int boxSize) : boxSize(boxSize) {
    cap.open(camIndex);
    if (!cap.isOpened()) throw runtime_error("Failed to open webcam");
}

CubeScanner::~CubeScanner() {
    cap.release();
    destroyAllWindows();
}

RubbixCube::Color CubeScanner::classifyColor(const Vec3b& bgr) {
    Mat bgrPixel(1, 1, CV_8UC3, bgr);
    Mat hsvPixel;
    cvtColor(bgrPixel, hsvPixel, COLOR_BGR2HSV);
    Vec3b hsv = hsvPixel.at<Vec3b>(0, 0);
    int h = hsv[0];
    int s = hsv[1];
    int v = hsv[2];

    int b = bgr[0];
    int g = bgr[1];
    int r = bgr[2];

    // 1. White detection (low saturation or balanced components)
    if (s < 55 && v > 120) return RubbixCube::Color::White;
    if (r > 140 && g > 140 && b > 140 &&
        abs(r - g) < 35 && abs(g - b) < 35 && abs(b - r) < 35) {
        return RubbixCube::Color::White;
    }

    // 2. Blue detection (Hue 85..135)
    if (h >= 85 && h <= 135) return RubbixCube::Color::Blue;

    // 3. Green detection (Hue 40..84)
    if (h >= 40 && h <= 84) return RubbixCube::Color::Green;

    // Green-to-Red ratio: decisive factor for distinguishing Red from Orange & Yellow
    double g_r_ratio = (double)g / max(1, r);

    // 4. Yellow detection (Hue 22..39 with high G/R, or high brightness)
    if ((h >= 22 && h <= 39 && g_r_ratio >= 0.65) ||
        (h >= 19 && g_r_ratio >= 0.70 && r > 100 && g > 100)) {
        return RubbixCube::Color::Yellow;
    }

    // 5. Red wrap-around zone (OpenCV Hue 160..180)
    if (h >= 160) return RubbixCube::Color::Red;

    // 6. Red vs Orange in the warm spectrum (0 <= Hue < 22)
    // - Red stickers: very low Green (G/R < 0.35, low G)
    // - Orange stickers: substantial Green (G/R >= 0.37, G >= 55)
    if (h <= 4 && g_r_ratio < 0.35) return RubbixCube::Color::Red;
    if (h >= 18 && g_r_ratio >= 0.35) return RubbixCube::Color::Orange;

    // Transition zone (5 <= Hue < 18):
    if (g_r_ratio >= 0.37 && g >= 55) {
        return RubbixCube::Color::Orange;
    } else if (g_r_ratio < 0.35) {
        return RubbixCube::Color::Red;
    } else {
        return (h >= 10 && g >= 60) ? RubbixCube::Color::Orange : RubbixCube::Color::Red;
    }
}

Vec3b CubeScanner::medianColor(const Mat& frame, int centerX, int centerY, int region) {
    int half = region / 2;
    vector<uchar> B, G, R;
    for (int dy = -half; dy <= half; ++dy)
        for (int dx = -half; dx <= half; ++dx) {
            int x = centerX + dx, y = centerY + dy;
            if (x >= 0 && x < frame.cols && y >= 0 && y < frame.rows) {
                Vec3b bgr = frame.at<Vec3b>(y, x);
                B.push_back(bgr[0]); G.push_back(bgr[1]); R.push_back(bgr[2]);
            }
        }
    sort(B.begin(), B.end()); sort(G.begin(), G.end()); sort(R.begin(), R.end());
    int mid = B.size() / 2;
    return Vec3b(B[mid], G[mid], R[mid]);
}

vector<vector<RubbixCube::Color>> CubeScanner::captureFace() {
    Mat frame;
    int rows, cols;

    while (true) {
        cap >> frame;
        rows = frame.rows; cols = frame.cols;
        int startX = (cols - 3 * boxSize) / 2;
        int startY = (rows - 3 * boxSize) / 2;

        for (int i = 0; i <= 3; ++i) {
            line(frame, Point(startX, startY + i * boxSize), Point(startX + 3 * boxSize, startY + i * boxSize), Scalar(0, 255, 0), 2);
            line(frame, Point(startX + i * boxSize, startY), Point(startX + i * boxSize, startY + 3 * boxSize), Scalar(0, 255, 0), 2);
        }

        // Live preview dots and letters inside grid
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                int cx = startX + j * boxSize + boxSize / 2;
                int cy = startY + i * boxSize + boxSize / 2;
                Vec3b cellBgr = medianColor(frame, cx, cy);
                RubbixCube::Color col = classifyColor(cellBgr);
                circle(frame, Point(cx, cy), 14, colorMap.at(col), FILLED);
                circle(frame, Point(cx, cy), 14, Scalar(0, 0, 0), 2);
                char letter = RubbixCube::getColorLetter(col);
                string strLetter(1, letter);
                Scalar txtCol = (col == RubbixCube::Color::White || col == RubbixCube::Color::Yellow) ? Scalar(0, 0, 0) : Scalar(255, 255, 255);
                putText(frame, strLetter, Point(cx - 5, cy + 5), FONT_HERSHEY_SIMPLEX, 0.5, txtCol, 2);
            }
        }

        putText(frame, "Press SPACE to capture | Live: R=Red, O=Orange", Point(20, 30), FONT_HERSHEY_SIMPLEX, 0.65, Scalar(0, 255, 255), 2, LINE_AA);
        imshow("Align Cube Face", frame);
        if (waitKey(30) == 32) break;
    }

    cap >> frame;
    int startX = (cols - 3 * boxSize) / 2;
    int startY = (rows - 3 * boxSize) / 2;

    vector<vector<RubbixCube::Color>> face(3, vector<RubbixCube::Color>(3));
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            int x = startX + j * boxSize + boxSize / 2;
            int y = startY + i * boxSize + boxSize / 2;
            Vec3b bgr = medianColor(frame, x, y);
            face[i][j] = classifyColor(bgr);
        }
    return face;
}

Mat CubeScanner::drawColorFace(const vector<vector<RubbixCube::Color>>& faceGrid) {
    int gridSize = 3 * boxSize;
    int padding = 50;
    Mat result(gridSize + padding, gridSize, CV_8UC3, Scalar(0, 0, 0));

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            Rect box(j * boxSize, i * boxSize, boxSize, boxSize);
            rectangle(result, box, colorMap.at(faceGrid[i][j]), FILLED);
            rectangle(result, box, Scalar(0, 0, 0), 2);

            char letter = RubbixCube::getColorLetter(faceGrid[i][j]);
            string strLetter(1, letter);
            Scalar txtCol = (faceGrid[i][j] == RubbixCube::Color::White || faceGrid[i][j] == RubbixCube::Color::Yellow) ? Scalar(0, 0, 0) : Scalar(255, 255, 255);
            putText(result, strLetter, Point(j * boxSize + boxSize / 2 - 8, i * boxSize + boxSize / 2 + 8), FONT_HERSHEY_SIMPLEX, 0.7, txtCol, 2);
        }

    putText(result, "Press [R] to rescan or [N] for next", Point(10, gridSize + 35), FONT_HERSHEY_SIMPLEX, 0.45, Scalar(255, 255, 255), 1, LINE_AA);
    return result;
}

Mat CubeScanner::drawFullCube(const vector<vector<vector<RubbixCube::Color>>>& cubeGrid) {
    int gap = 5, w = 12 * boxSize, h = 9 * boxSize;
    Mat canvas(h, w, CV_8UC3, Scalar(30, 30, 30));

    auto drawFace = [&](int faceIndex, int row, int col) {
        Point topLeft(col * boxSize, row * boxSize);
        rectangle(canvas, Rect(topLeft, Size(3 * boxSize, 3 * boxSize)), Scalar(255, 255, 255), 4);

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                int x = (col + j) * boxSize;
                int y = (row + i) * boxSize;
                Rect rect(x, y, boxSize - gap, boxSize - gap);
                rectangle(canvas, rect, colorMap.at(cubeGrid[faceIndex][i][j]), FILLED);
                rectangle(canvas, rect, Scalar(0, 0, 0), 2);

                char letter = RubbixCube::getColorLetter(cubeGrid[faceIndex][i][j]);
                string strLetter(1, letter);
                Scalar txtCol = (cubeGrid[faceIndex][i][j] == RubbixCube::Color::White || cubeGrid[faceIndex][i][j] == RubbixCube::Color::Yellow) ? Scalar(0, 0, 0) : Scalar(255, 255, 255);
                putText(canvas, strLetter, Point(x + (boxSize - gap) / 2 - 6, y + (boxSize - gap) / 2 + 6), FONT_HERSHEY_SIMPLEX, 0.45, txtCol, 1);
            }
    };

    drawFace(0, 0, 3);
    drawFace(1, 3, 0); drawFace(2, 3, 3); drawFace(3, 3, 6); drawFace(4, 3, 9);
    drawFace(5, 6, 3);

    return canvas;
}

void CubeScanner::scan(RubbixCube& cube) {
    vector<vector<vector<RubbixCube::Color>>> cubeGrid(6, vector<vector<RubbixCube::Color>>(3, vector<RubbixCube::Color>(3, RubbixCube::Color::White)));

    for (int face = 0; face < 6; face++) {
        while (true) {
            auto grid = captureFace();
            cubeGrid[face] = grid;

            Mat faceImg = drawColorFace(grid);
            Mat cubeImg = drawFullCube(cubeGrid);

            imshow("Scanned Face", faceImg);
            imshow("Cube Net", cubeImg);

            int key = waitKey(0);
            if (key == 'n' || key == 'N') {
                for (int i = 0; i < 3; ++i)
                    for (int j = 0; j < 3; ++j)
                        cube.setColor(static_cast<RubbixCube::Face>(face), i, j, grid[i][j]);
                destroyWindow("Scanned Face");
                break;
            }
        }
    }

    cap.release();
    destroyAllWindows();
}