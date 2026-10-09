#include "../Model/RubbixCube.h"

#ifndef RUBBIX_CUBE_SOLVER_BFSSOLVER_H
#define RUBBIX_CUBE_SOLVER_BFSSOLVER_H

template<typename T, typename H>
class BfsSolver{
    private:
        vector<RubbixCube::Move> moves;
        unordered_map<T,bool,H>visited;
        unordered_map<T,RubbixCube::Move,H>move_done;

        T bfs(){
            queue<T> q;
            q.push(rubikCube);
            visited[rubikCube] = true;
            while(!q.empty()){
                T node = q.front();
                q.pop();
                if(node.isSolved()){
                    return node;
                }
                for(int i = 0; i < 18; i++){
                    auto curMove = RubbixCube::Move(i);
                    node.move(curMove);
                    if(!visited[node]){
                        visited[node] = true;
                        move_done[node] = curMove;
                        q.push(node);
                    }
                    node.invert(curMove);
                }
            }
            return rubikCube;
        }
    public:
        T rubikCube;
        BfsSolver(T _rubikCube){
            rubikCube = _rubikCube;
        }

        vector<RubbixCube::Move> solve(){
            T solved_cube = bfs();
            assert(solved_cube.isSolved());
            T curCube = solved_cube;
            while(!(curCube == rubikCube)){
                RubbixCube::Move move = move_done[curCube];
                moves.push_back(move);
                curCube.invert(move);
            }
            rubikCube = solved_cube;
            reverse(moves.begin(), moves.end());
            return moves;
        }
};
#endif 