#ifndef CUBESCANNER_H
#define CUBESCANNER_H

#include <opencv2/opencv.hpp>
#include "../Model/RubbixCube.h"
#include <vector>
#include <map>

using namespace std;
using namespace cv;

class CubeScanner {
public:
    CubeScanner(int camIndex = 0, int boxSize = 60);
    ~CubeScanner();

    void scan(RubbixCube& cube);

private:
    VideoCapture cap;
    int boxSize;

    static const map<RubbixCube::Color, Scalar> colorMap;

    RubbixCube::Color classifyColor(const Vec3b& bgr);
    Vec3b medianColor(const Mat& frame, int centerX, int centerY, int region = 5);

    vector<vector<RubbixCube::Color>> captureFace();
    Mat drawColorFace(const vector<vector<RubbixCube::Color>>& faceGrid);
    Mat drawFullCube(const vector<vector<vector<RubbixCube::Color>>>& cubeGrid);
};

#endif