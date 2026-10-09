#include "RubbixCube.h"

class RubbixCubeBitBoard : public RubbixCube{
    private:
    int arr[3][3]={ {0,1,2},
                    {7,8,3},
                    {6,5,4}};
    //  b0  b1  b2 
    //  b7      b3
    //  b6  b5  b4
    
    /*
     *             b0 b1 b2
     *             b7    b3
     *             b6 b5 b4
     *
     *  b0 b1 b2   b0 b1 b2   b0 b1 b2   b0 b1 b2
     *  b7    b3   b7    b3   b7    b3   b7    b3
     *  b6 b5 b4   b6 b5 b4   b6 b5 b4   b6 b5 b4
     *
     *             b0 b1 b2
     *             b7    b3
     *             b6 b5 b4
     */

    uint64_t one8=(1<<8)-1,one24=(1<<24)-1;

    //helper function
    void rotateFace(int ind){
        uint64_t side=bitBoard[ind];
        side=side>>8*6;
        bitBoard[ind]=(bitBoard[ind]<<16) | (side);
    }

    void rotateSide(int s1,int s1_1,int s1_2,int s1_3,int s2,int s2_1,int s2_2,int s2_3){
        uint64_t clr_1=(bitBoard[s2] & (one8 << (8 * s2_1))) >> (8 * s2_1);
        uint64_t clr_2=(bitBoard[s2] & (one8 << (8 * s2_2))) >> (8 * s2_2);
        uint64_t clr_3=(bitBoard[s2] & (one8 << (8 * s2_3))) >> (8 * s2_3);
        
        bitBoard[s1]= (bitBoard[s1] & ~(one8 << (8 * s1_1))) | clr_1 << (8 * s1_1);
        bitBoard[s1]= (bitBoard[s1] & ~(one8 << (8 * s1_2))) | clr_2 << (8 * s1_2);
        bitBoard[s1]= (bitBoard[s1] & ~(one8 << (8 * s1_3))) | clr_3 << (8 * s1_3);
    }

    int get5bitCorner(string Corner){
        int ret=0; 
        string actualStr;
        for(auto c:Corner){
            if(c!='W' && c!='Y') continue;
            actualStr.push_back(c);
            if(c=='Y'){
                ret |= (1<<2);
            }
        }
        for(auto c:Corner){
            if(c!='R' && c!='O') continue;
            actualStr.push_back(c);
            if(c=='O'){
                ret |= (1<<1);
            }
        }
        for(auto c:Corner){
            if(c!='B' && c!='G') continue;
            actualStr.push_back(c);
            if(c=='G'){
                ret |= (1<<0);
            }
        }
        if(Corner[1]==actualStr[0]){
            ret |= (1<<3);
        }else if(Corner[2]==actualStr[0]){
            ret |= (1<<3);
        }
        return ret;
    }
    //  this function was used for testing
    //      void print5bitbin(int a){
    //          for(int i=4; i>=0; i--){
    //              if(a &(1<<i))cout<<1;
    //              else cout<<0;
    //          }
    //      }
    public:
    uint64_t solvedSideConfig[6]{};
    uint64_t bitBoard[6]{};
    /*for solved cube
    index           B7 B6 B5 B4 B3 B2 B1 B0
    bitBoard[0]= 0x 01 01 01 01 01 01 01 01 up
    bitBoard[1]= 0x 02 02 02 02 02 02 02 02 left
    bitBoard[2]= 0x 04 04 04 04 04 04 04 04 front
    bitBoard[3]= 0x 08 08 08 08 08 08 08 08 right
    bitBoard[4]= 0x 10 10 10 10 10 10 10 10 back
    bitBoard[5]= 0x 20 20 20 20 20 20 20 20 down
    */
    RubbixCubeBitBoard(){
        for(int side=0; side<6; side++){
            uint64_t clear=1ULL<<side;
            bitBoard[side]=0;
            for(int face=0; face<8; face++){
                bitBoard[side] |= (clear<<(8*face));
            }
            solvedSideConfig[side]=bitBoard[side];
        }
    }

    bool isSolved() const override{
        for(int i=0; i<6; i++){
            if(solvedSideConfig[i]!=bitBoard[i]) return false;
        }
        return true;
    }

    Color getColor(Face face, unsigned row, unsigned col) const override{
        int ind=arr[row][col];
        if(ind== 8)return (Color)((int)face);

        uint64_t side =bitBoard[(int)face];
        uint64_t color=(side>>(8*ind))&one8;
        int bitPos=0;
        while(color!=0){
            color=color>>1;
            bitPos++;
        }
        return (Color)(bitPos-1);
    }

    void setColor(Face face, unsigned row, unsigned col, Color color) override{
        int ind=arr[row][col];
        if(ind < 8){
            bitBoard[(int)face] = (bitBoard[(int)face] & ~(0xFFULL << (8 * ind))) | ((uint64_t)(1ULL << (int)color) << (8 * ind));
        }
    }

    RubbixCube &u() override{
        this->rotateFace(0);
        uint64_t temp= bitBoard[2] & one24;
        bitBoard[2]= (bitBoard[2] & ~one24) | (bitBoard[3] & one24);
        bitBoard[3]= (bitBoard[3] & ~one24) | (bitBoard[4] & one24);
        bitBoard[4]= (bitBoard[4] & ~one24) | (bitBoard[1] & one24);
        bitBoard[1]= (bitBoard[1] & ~one24) | (temp);
        return *this;
    }
    RubbixCube &u_inv() override{
        this->u();
        this->u();
        this->u();
        return *this;
    }
    RubbixCube &u2() override{
        this->u();
        this->u();
        return *this;
    }

    RubbixCube &f() override{
        rotateFace(2);
        uint64_t clr_1=(bitBoard[0] & (one8 << (8 * 4))) >> (8 * 4);
        uint64_t clr_2=(bitBoard[0] & (one8 << (8 * 5))) >> (8 * 5);
        uint64_t clr_3=(bitBoard[0] & (one8 << (8 * 6))) >> (8 * 6);

        this->rotateSide(0,4,5,6,1,2,3,4);
        this->rotateSide(1,2,3,4,5,0,1,2);
        this->rotateSide(5,0,1,2,3,6,7,0);
        
        bitBoard[3]= (bitBoard[3] & ~(one8 << (8 * 6))) | clr_1 << (8 * 6);
        bitBoard[3]= (bitBoard[3] & ~(one8 << (8 * 7))) | clr_2 << (8 * 7);
        bitBoard[3]= (bitBoard[3] & ~(one8 << (8 * 0))) | clr_3 << (8 * 0);
        return *this;
    }
    RubbixCube &f_inv() override{
        this->f();
        this->f();
        this->f();
        return *this;
    }
    RubbixCube &f2() override{
        this->f();
        this->f();
        return *this;
    }

    RubbixCube &b() override{
        rotateFace(4);
        uint64_t clr_1=(bitBoard[0] & (one8 << (8 * 0))) >> (8 * 0);
        uint64_t clr_2=(bitBoard[0] & (one8 << (8 * 1))) >> (8 * 1);
        uint64_t clr_3=(bitBoard[0] & (one8 << (8 * 2))) >> (8 * 2);

        this->rotateSide(0,0,1,2,3,2,3,4);
        this->rotateSide(3,2,3,4,5,4,5,6);
        this->rotateSide(5,4,5,6,1,6,7,0);
        
        bitBoard[1]= (bitBoard[1] & ~(one8 << (8 * 6))) | clr_1 << (8 * 6);
        bitBoard[1]= (bitBoard[1] & ~(one8 << (8 * 7))) | clr_2 << (8 * 7);
        bitBoard[1]= (bitBoard[1] & ~(one8 << (8 * 0))) | clr_3 << (8 * 0);
        return *this;
    }
    RubbixCube &b_inv() override{
        this->b();
        this->b();
        this->b();
        return *this;
    }
    RubbixCube &b2() override{
        this->b();
        this->b();
        return *this;
    }

    RubbixCube &r() override{
        rotateFace(3);
        uint64_t clr_1=(bitBoard[0] & (one8 << (8 * 2))) >> (8 * 2);
        uint64_t clr_2=(bitBoard[0] & (one8 << (8 * 3))) >> (8 * 3);
        uint64_t clr_3=(bitBoard[0] & (one8 << (8 * 4))) >> (8 * 4);

        this->rotateSide(0,2,3,4,2,2,3,4);
        this->rotateSide(2,2,3,4,5,2,3,4);
        this->rotateSide(5,2,3,4,4,6,7,0);
        
        bitBoard[4]= (bitBoard[4] & ~(one8 << (8 * 6))) | clr_1 << (8 * 6);
        bitBoard[4]= (bitBoard[4] & ~(one8 << (8 * 7))) | clr_2 << (8 * 7);
        bitBoard[4]= (bitBoard[4] & ~(one8 << (8 * 0))) | clr_3 << (8 * 0);
        return *this;
    }
    RubbixCube &r_inv() override{
        this->r();
        this->r();
        this->r();
        return *this;
    }
    RubbixCube &r2() override{
        this->r();
        this->r();
        return *this;
    }

    RubbixCube &l() override{
        this->rotateFace(1);
        uint64_t clr_1=(bitBoard[2] & (one8 << (8 * 0))) >> (8 * 0);
        uint64_t clr_2=(bitBoard[2] & (one8 << (8 * 6))) >> (8 * 6);
        uint64_t clr_3=(bitBoard[2] & (one8 << (8 * 7))) >> (8 * 7);

        this->rotateSide(2, 0, 7, 6, 0, 0, 7, 6);
        this->rotateSide(0, 0, 7, 6, 4, 4, 3, 2);
        this->rotateSide(4, 4, 3, 2, 5, 0, 7, 6);

        bitBoard[5]=(bitBoard[5] & ~(one8 << (8 * 0))) | (clr_1 << (8 * 0));
        bitBoard[5]=(bitBoard[5] & ~(one8 << (8 * 6))) | (clr_2 << (8 * 6));
        bitBoard[5]=(bitBoard[5] & ~(one8 << (8 * 7))) | (clr_3 << (8 * 7));
        return *this;
    }
    RubbixCube &l_inv() override{
        this->l();
        this->l();
        this->l();
        return *this;
    }
    RubbixCube &l2() override{
        this->l();
        this->l();
        return *this;
    }
    
    RubbixCube &d() override{
        this->rotateFace(5);
        uint64_t clr_1 = (bitBoard[2] & (one8 << (8 * 4))) >> (8 * 4);
        uint64_t clr_2 = (bitBoard[2] & (one8 << (8 * 5))) >> (8 * 5);
        uint64_t clr_3 = (bitBoard[2] & (one8 << (8 * 6))) >> (8 * 6);

        this->rotateSide(2, 4, 5, 6, 1, 4, 5, 6);
        this->rotateSide(1, 4, 5, 6, 4, 4, 5, 6);
        this->rotateSide(4, 4, 5, 6, 3, 4, 5, 6);

        bitBoard[3] = (bitBoard[3] & ~(one8 << (8 * 4))) | (clr_1 << (8 * 4));
        bitBoard[3] = (bitBoard[3] & ~(one8 << (8 * 5))) | (clr_2 << (8 * 5));
        bitBoard[3] = (bitBoard[3] & ~(one8 << (8 * 6))) | (clr_3 << (8 * 6));
        return *this;
    }
    RubbixCube &d_inv() override{
        this->d();
        this->d();
        this->d();
        return *this;}
    RubbixCube &d2() override{
        this->d();
        this->d();
        return *this;
    }
    bool operator==(const RubbixCubeBitBoard &r1) const{
        for(int i=0; i<6; i++){
            if(bitBoard[i]!=r1.bitBoard[i]) return false;
        }
        return true;
    }

    RubbixCubeBitBoard &operator=(const RubbixCubeBitBoard &r1){
        for(int i=0; i<6; i++){
            bitBoard[i]=r1.bitBoard[i];
        }
        return *this;
    }

    uint64_t getCorners(){
        uint64_t ret =0;
        string top_front_right ="";
        top_front_right =getColorLetter(getColor(Face::Up,2,2));
        top_front_right =getColorLetter(getColor(Face::Front,0,2));
        top_front_right =getColorLetter(getColor(Face::Right,0,0));

        string top_front_left ="";
        top_front_left =getColorLetter(getColor(Face::Up,2,0));
        top_front_left =getColorLetter(getColor(Face::Front,0,0));
        top_front_left =getColorLetter(getColor(Face::Left,0,2));

        string top_back_right ="";
        top_back_right =getColorLetter(getColor(Face::Up,0,2));
        top_back_right =getColorLetter(getColor(Face::Back,0,0));
        top_back_right =getColorLetter(getColor(Face::Right,0,2));
        
        string top_back_left ="";
        top_back_left =getColorLetter(getColor(Face::Up,0,0));
        top_back_left =getColorLetter(getColor(Face::Back,0,2));
        top_back_left =getColorLetter(getColor(Face::Left,0,0));
        
        string bottom_front_right ="";
        bottom_front_right =getColorLetter(getColor(Face::Down,0,2));
        bottom_front_right =getColorLetter(getColor(Face::Front,2,2));
        bottom_front_right =getColorLetter(getColor(Face::Right,2,0));
        
        string bottom_front_left ="";
        bottom_front_left =getColorLetter(getColor(Face::Down,0,0));
        bottom_front_left =getColorLetter(getColor(Face::Front,2,0));
        bottom_front_left =getColorLetter(getColor(Face::Left,2,2));
        
        string bottom_back_right ="";
        bottom_back_right =getColorLetter(getColor(Face::Down,2,2));
        bottom_back_right =getColorLetter(getColor(Face::Back,2,0));
        bottom_back_right =getColorLetter(getColor(Face::Right,2,2));
        
        string bottom_back_left ="";
        bottom_back_left =getColorLetter(getColor(Face::Down,2,0));
        bottom_back_left =getColorLetter(getColor(Face::Back,2,2));
        bottom_back_left =getColorLetter(getColor(Face::Left,2,0));

        ret |= get5bitCorner(top_front_right);
        ret = ret<<5;

        ret |= get5bitCorner(top_front_left);
        ret = ret<<5;
        
        ret |= get5bitCorner(top_back_right);
        ret = ret<<5;
        
        ret |= get5bitCorner(top_back_left);
        ret = ret<<5;
        
        ret |= get5bitCorner(bottom_front_right);
        ret = ret<<5;
        
        ret |= get5bitCorner(bottom_front_left);
        ret = ret<<5;
        
        ret |= get5bitCorner(bottom_back_right);
        ret = ret<<5;
        
        ret |= get5bitCorner(bottom_back_left);
        ret = ret<<5;

        //testing
            // cout<<top_front_right<<" "; 
            // print5bitbin(get5bitCorner(top_front_right));
            // cout<<"\n";
            // cout<<top_front_left<<" "; 
            // print5bitbin(get5bitCorner(top_front_left));
            // cout<<"\n";
            // cout<<top_back_right<<" "; 
            // print5bitbin(get5bitCorner(top_back_right));
            // cout<<"\n";
            // cout<<top_back_left<<" "; 
            // print5bitbin(get5bitCorner(top_back_left));
            // cout<<"\n";
            // cout<<bottom_front_right<<" "; 
            // print5bitbin(get5bitCorner(bottom_front_right));
            // cout<<"\n";
            // cout<<bottom_front_left<<" "; 
            // print5bitbin(get5bitCorner(bottom_front_left));
            // cout<<"\n";
            // cout<<bottom_back_right<<" "; 
            // print5bitbin(get5bitCorner(bottom_back_right));
            // cout<<"\n";
            // cout<<bottom_back_left<<" "; 
            // print5bitbin(get5bitCorner(bottom_back_left));
            // cout<<"\n";
        return ret;
    }
};

struct HashBitBoard{
    size_t operator()(const RubbixCubeBitBoard &r1)const {
        uint64_t final_hash=r1.bitBoard[0];
        for(int i=1; i<6; i++)final_hash^=r1.bitBoard[i];
    return (size_t) final_hash;
    }
};