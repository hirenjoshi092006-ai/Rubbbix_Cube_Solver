#include "../Model/RubbixCube.h"

#ifndef RUBBIX_CUBE_SOLVER_DFSSOLVER_H
#define RUBBIX_CUBE_SOLVER_DFSSOLVER_H

template<typename T, typename H>
class DfsSolver{
    private:
        vector<RubbixCube::Move> moves;
        int max_searchingDepth;

        bool dfs(int dep){
            if(rubikCube.isSolved()) return true;
            if(dep > max_searchingDepth) return false;
            for(int i = 0; i < 18; i++){
                rubikCube.move(RubbixCube::Move(i));
                moves.push_back(RubbixCube::Move(i));
                if(dfs(dep + 1)) return true;
                moves.pop_back();
                rubikCube.invert(RubbixCube::Move(i));
            }
            return false;
        }
    public:
        T rubikCube;
        DfsSolver(T _rubikCube, int _max_searchingDepth = 8){
            rubikCube = _rubikCube;
            max_searchingDepth = _max_searchingDepth;
        }

        vector<RubbixCube::Move> solve(){
            dfs(1);
            return moves;
        }
};
#endif 