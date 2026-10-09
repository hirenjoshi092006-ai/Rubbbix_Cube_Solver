#ifndef RUBBIX_CUBE_SOLVER_CORNERRATTERNDATABASE_H
#define RUBBIX_CUBE_SOLVER_CORNERRATTERNDATABASE_H

#include "../Model/RubbixCube.h"
#include "PatternDatabase.h"
#include "Permutation_Indexer.h"
using namespace std;

class CornerPatternDatabase : public PatternDatabase{
    Permutation_indexer<8>permuind;
    public:
        CornerPatternDatabase();
        CornerPatternDatabase(uint8_t init_val);
        uint32_t getDatabaseIndex(const RubbixCube &Cube) const;
};

#endif 