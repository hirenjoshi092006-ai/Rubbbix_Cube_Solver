#include "CornerDbMaker.h"
using namespace std;

CornerDBMaker::CornerDBMaker(string _fileName){
    fileName =_fileName;
}
CornerDBMaker::CornerDBMaker(string _fileName,uint8_t init_val){
    fileName =_fileName;
    CornerDB =CornerPatternDatabase(init_val);
}

bool CornerDBMaker::bfsAndStore(){
    RubbixCubeBitBoard Cube;
    queue<RubbixCubeBitBoard> q;
    q.push(Cube);
    CornerDB.setNumMoves(Cube,0);
    int curr_depth=0;
    while(!q.empty()){
        int n=q.size();
        curr_depth++;
        if(curr_depth==9)break;
        for(int count=0; count<n; count++){
            RubbixCubeBitBoard node =q.front();
            q.pop();
            for(int i=0; i<18; i++){
                auto curr_move =RubbixCube::Move(i);
                node.move(curr_move);
                if((int) CornerDB.getNumMoves(node)>curr_depth){
                    CornerDB.setNumMoves(node,curr_depth);
                    q.push(node);
                }
                node.invert(curr_move);
            }
        }
    }
    CornerDB.toFile(fileName);
    return true;
}