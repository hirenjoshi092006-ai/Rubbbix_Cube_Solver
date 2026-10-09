#ifndef RUBIKS_CUBE_SOLVER_PATTERNDATABASE_H
#define RUBIKS_CUBE_SOLVER_PATTERNDATABASE_H

#include "../Model/RubbixCube.h"
#include "NibbleArray.h"
using namespace std;

class PatternDatabase {
    private:
        NibbleArray Database;
        size_t size;
        size_t numItems;
    public:
        PatternDatabase(const size_t size);
        //testing init_val
        PatternDatabase(const size_t size,const uint8_t init_val);

        virtual uint32_t getDatabaseIndex(const RubbixCube &Cube) const=0;

        virtual bool setNumMoves(const RubbixCube &Cube,uint8_t numMoves);

        virtual bool setNumMoves(const uint32_t ind,uint8_t numMoves);

        virtual uint8_t getNumMoves(const RubbixCube &Cube)const;

        virtual uint8_t getNumMoves(const uint32_t ind)const;

        virtual size_t getSize() const;
        
        virtual size_t getNumsItems() const;
        
        virtual bool isFull() const;
        
        virtual void toFile(const string &filePath) const;
        
        virtual bool fromFile(const string &filePath);
        
        virtual vector<uint8_t> inflate()const;
        
        virtual void reset();
    };
#endif 