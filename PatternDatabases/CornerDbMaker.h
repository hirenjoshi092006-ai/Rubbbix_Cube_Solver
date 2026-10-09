#ifndef RUBBIX_CUBE_SOLVER_CORNERBDMAKER_H
#define RUBBIX_CUBE_SOLVER_CORNERBDMAKER_H

#include "CornerPatternDatabase.h"
#include "../Model/RubbixCubeBitBoard.cpp"
using namespace std;

class CornerDBMaker{
    private:    
        string fileName;
        CornerPatternDatabase CornerDB;

    public:
        CornerDBMaker(string _fileName);
        CornerDBMaker(string _fileName,uint8_t init_val);
    bool bfsAndStore();
};
#endif 