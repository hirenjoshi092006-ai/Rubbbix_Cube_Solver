#include "../Model/RubbixCube.h"
#include "DfsSolver.h"

#ifndef RUBBIX_CUBE_SOLVER_IdDFSSOLVER_H
#define RUBBIX_CUBE_SOLVER_IdDFSSOLVER_H

template<typename T, typename H>
class IdDfsSolver{
    private:
        vector<RubbixCube::Move> moves;
        int max_searchingDepth;

    public:
        T rubikCube;
        IdDfsSolver(T _rubikCube, int _max_searchingDepth = 7){
            rubikCube = _rubikCube;
            max_searchingDepth = _max_searchingDepth;
        }

        vector<RubbixCube::Move> solve(){
            for(int i = 1; i <= max_searchingDepth; i++){
                DfsSolver<T, H> dfsSolver(rubikCube, i);
                moves = dfsSolver.solve();
                if(dfsSolver.rubikCube.isSolved()){
                    rubikCube = dfsSolver.rubikCube;
                    break;
                }
            }
            return moves;
        }
};
#endif 