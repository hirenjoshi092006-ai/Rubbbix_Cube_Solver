#ifndef RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H
#define RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H

#include<bits/stdc++.h>
using namespace std;

/*
 * A base class for all Rubik's Cube Model.There are various representation for Rubik's Cube.
 * Each one has it's own special ways of definitions. This class provides a shared functionality
 * between all models.
 * We'll benchmark all models and observe which one is better for performance.
 */

class RubbixCube
{
public:
    enum class Color{
        White,
        Green,
        Red,
        Blue,
        Orange,
        Yellow
    };

    enum class Move{
        l1,l_inv,l2,
        r1,r_inv,r2,
        u1,u_inv,u2,
        d1,d_inv,d2,
        f1,f_inv,f2,
        b1,b_inv,b2
    };

    enum class Face{
        Up,
        Left,
        Front,
        Right,
        Back,
        Down
    };

    /*
     * Returns the color of the cell at (row, col) in face.
     * If Rubik's Cube face is pointing at you, then the row numbering starts from the
     * top to bottom, and column numbering starts from the left to right.
     * The rows and columns are 0-indexed.
     * @param Face, row, and column index
     */
    virtual Color getColor(Face face, unsigned row, unsigned col) const=0;
    
    // Set the color of the cell at (row, col) in face
    virtual void setColor(Face face, unsigned row, unsigned col, Color color)=0;
    
    // return first character of Color 
    static char getColorLetter(Color color);

    // return boolen value is cube is solved or not
    virtual bool isSolved() const=0;

    //return move in string format
    static string getMove(Move ind);

        /*
     * Print the Rubik Cube in Planar format.
     *
     * The cube is laid out as follows.
     *
     * The sides:
     *    U
     *  L F R B
     *    D
     *
     * Color wise:
     *
     *          W W W
     *          W W W
     *          W W W
     *
     *  G G G   R R R   B B B   O O O
     *  G G G   R R R   B B B   O O O
     *  G G G   R R R   B B B   O O O
     *
     *          Y Y Y
     *          Y Y Y
     *          Y Y Y
     *
     * Row and Column Numberings:
     * rx -> row numbering
     * cx -> column numbering
     * bx -> both row and column numbering
     *
     *             b0 c1 c2
     *             r1  .  .
     *             r2  .  .
     *
     *  b0 c1 c2   b0 c1 c2   b0 c1 c2   b0 c1 c2
     *  r1  .  .   r1  .  .   r1  .  .   r1  .  .
     *  r2  .  .   r2  .  .   r2  .  .   r2  .  .
     *
     *             b0 c1 c2
     *             r1  .  .
     *             r2  .  .
     */
    void print() const;

    //random shuffle the cube with 'times' move and returns  the moves performed
    vector<Move> RandomShuffleCube(unsigned int times);

    //performed move in rubbix cube
    RubbixCube &move(Move ind);

    //invert a move
    RubbixCube &invert(Move ind);

    /*
     * Rotational Moves on the Rubik Cubes
     *
     * F, F’, F2,
     * U, U’, U2,
     * L, L’, L2,
     * D, D’, D2,
     * R, R’, R2,
     * B, B’, B2
     */
    virtual RubbixCube &f()=0;
    virtual RubbixCube &f_inv()=0;
    virtual RubbixCube &f2()=0;

    virtual RubbixCube &b()=0;
    virtual RubbixCube &b_inv()=0;
    virtual RubbixCube &b2()=0;
    
    virtual RubbixCube &r()=0;
    virtual RubbixCube &r_inv()=0;
    virtual RubbixCube &r2()=0;
    
    virtual RubbixCube &l()=0;
    virtual RubbixCube &l_inv()=0;
    virtual RubbixCube &l2()=0;
    
    virtual RubbixCube &u()=0;
    virtual RubbixCube &u_inv()=0;
    virtual RubbixCube &u2()=0;
    
    virtual RubbixCube &d()=0;
    virtual RubbixCube &d_inv()=0;
    virtual RubbixCube &d2()=0;

    //Other helper function
    string getCornerColorString(uint8_t ind) const;
    uint8_t getCornerIndex(uint8_t ind) const;
    uint8_t getCornerOrientation(uint8_t ind) const;

};

#endif