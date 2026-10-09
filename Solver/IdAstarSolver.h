#include "../Model/RubbixCube.h"
#include "../PatternDatabases/CornerPatternDatabase.h"

#ifndef RUBBIX_CUBE_SOLVER_IDASTARSOLVER_H
#define RUBBIX_CUBE_SOLVER_IDASTARSOLVER_H

template<typename T, typename H>
class IdAstarSolver{
    private:
        vector<RubbixCube::Move> moves;
        CornerPatternDatabase cornerDB;
        unordered_map<T, RubbixCube::Move, H> move_done;
        unordered_map<T, bool, H> visited;

        struct Node{
            T Cube;
            int depth;
            int estimate;
            Node(T _cube, int _depth, int _estimate) : Cube(_cube), depth(_depth), estimate(_estimate) {}
        };

        struct compareCube{
            bool operator()(pair<Node, int> const &p1, pair<Node, int> const &p2){
                auto n1 = p1.first, n2 = p2.first;
                if(n1.depth + n1.estimate == n2.depth + n2.estimate){
                    return n1.estimate > n2.estimate;
                } else {
                    return n1.depth + n1.estimate > n2.depth + n2.estimate;
                }
            }
        };

        void resetStructure(){
            moves.clear();
            move_done.clear();
            visited.clear();
        }

    // return {solved cube, bound}: if the cube was solved
    // return {rubikCube, next_bound}: if the cube was not solved
    pair<T, int> IdAstar(int bound){
        // priority queue contains pair(node, move done to reach that)
        priority_queue<pair<Node, int>, vector<pair<Node, int>>, compareCube> pq;
        Node start = Node(rubikCube, 0, cornerDB.getNumMoves(rubikCube));
        pq.push(make_pair(start, 0));
        int next_bound = 100;
        while(!pq.empty()){
            auto p = pq.top();
            Node node = p.first;
            pq.pop();

            if(visited[node.Cube]) continue;
            visited[node.Cube] = true;

            move_done[node.Cube] = RubbixCube::Move(p.second);
            if(node.Cube.isSolved()) return make_pair(node.Cube, bound);
            node.depth++;

            for(int i = 0; i < 18; i++){
                auto curr_move = RubbixCube::Move(i);
                node.Cube.move(curr_move);
                if(!visited[node.Cube]){
                    node.estimate = cornerDB.getNumMoves(node.Cube);
                    if(node.estimate + node.depth > bound){
                        next_bound = min(next_bound, node.estimate + node.depth);
                    } else {
                        pq.push(make_pair(node, i));
                    }
                }
                node.Cube.invert(curr_move);
            }
        }
        return make_pair(rubikCube, next_bound);
    }
    public:
        T rubikCube;
        IdAstarSolver(T _rubikCube, string fileName){
            rubikCube = _rubikCube;
            cornerDB.fromFile(fileName);
        }
        vector<RubbixCube::Move> solve(){
            int bound = 1;
            auto p = IdAstar(bound);
            while(p.second != bound){
                resetStructure();
                bound = p.second;
                p = IdAstar(bound);
            }
            T solved_cube = p.first;
            assert(solved_cube.isSolved());
            T curr_cube = solved_cube;
            while(!(curr_cube == rubikCube)){
                RubbixCube::Move curr_move = move_done[curr_cube];
                moves.push_back(curr_move);
                curr_cube.invert(curr_move);
            }
            rubikCube = solved_cube;
            reverse(moves.begin(), moves.end());
            return moves;
        }
};
#endif // RUBBIX_CUBE_SOLVER_IDASTARSOLVER_H 