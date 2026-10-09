#include "RubbixCube.h"

class RubbixCube1Darray : public RubbixCube{
    private:
    static inline int getIndex(int ind,int row,int col){
        return (ind*9)+(row*3)+col;
    }
    //Helper function
    void rotateFace(int ind){
        char temp[9]={};
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                temp[i*3+j]=cube[getIndex(ind,i,j)];
            }
        }
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cube[getIndex(ind,j,2-i)]=temp[i*3+j];
            }
        }
    }
    
    void rotateFace_inv(int ind){
        char temp[9]={};
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                temp[i*3+j]=cube[getIndex(ind,i,j)];
            }
        }
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cube[getIndex(ind,2-j,i)]=temp[i*3+j];
            }
        }
    }
    void rotateFace_twice(int ind){
        char temp[9]={};
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                temp[i*3+j]=cube[getIndex(ind,i,j)];
            }
        }
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cube[getIndex(ind,j,i)]=temp[i*3+j];
            }
        }
    }
    public:
    //      0
    //  1   2   3   4
    //      5
    char cube[54];

    //constructor
    RubbixCube1Darray(){
        for(int i=0; i<6; i++){
            for(int j=0; j<3; j++){
                for(int k=0; k<3; k++){
                    cube[i*9+j*3+k]=getColorLetter(Color(i));
                }
            }
        }
    }

    bool isSolved() const override{
        for(int i=0; i<6; i++){
            for(int j=0; j<3; j++){
                for(int k=0; k<3; k++){
                    if(this->cube[getIndex(i,j,k)]==getColorLetter(Color(i))) continue;
                    return false;
                }
            }
        }
        return true;
    }

    Color getColor(Face face, unsigned row, unsigned col) const override{
        char color=cube[getIndex((int)face,(int)row,(int)col)];
        switch(color){
            case 'W':
            return Color::White;
            case 'Y':
            return Color::Yellow;
            case 'R':
            return Color::Red;
            case 'O':
            return Color::Orange;
            case 'G':
            return Color::Green;
            case 'B':
            return Color::Blue;
            default:
            return Color::White;
        }
    }

    void setColor(Face face, unsigned row, unsigned col, Color color) override{
        cube[getIndex((int)face, (int)row, (int)col)] = getColorLetter(color);
    }

    RubbixCube &u() override{
        this->rotateFace(0);
        char temp[3]={};
        for(int i=0; i<3; i++) temp[i]=cube[getIndex(4,0,2-i)];
        for(int i=0; i<3; i++) cube[getIndex(4,0,2-i)]=cube[getIndex(1,0,2-i)];
        for(int i=0; i<3; i++) cube[getIndex(1,0,2-i)]=cube[getIndex(2,0,2-i)];
        for(int i=0; i<3; i++) cube[getIndex(2,0,2-i)]=cube[getIndex(3,0,2-i)];
        for(int i=0; i<3; i++) cube[getIndex(3,0,2-i)]=temp[i];
        return *this;
    }

    RubbixCube &u_inv() override{
        this->rotateFace_inv(0);
        char temp[3]={};
        for(int i=0; i<3; i++) temp[i]=cube[getIndex(4,0,2-i)];
        for(int i=0; i<3; i++) cube[getIndex(4,0,2-i)]=cube[getIndex(3,0,2-i)];
        for(int i=0; i<3; i++) cube[getIndex(3,0,2-i)]=cube[getIndex(2,0,2-i)];
        for(int i=0; i<3; i++) cube[getIndex(2,0,2-i)]=cube[getIndex(1,0,2-i)];
        for(int i=0; i<3; i++) cube[getIndex(1,0,2-i)]=temp[i];
        return *this;
    }

    RubbixCube &u2() override{
        this->rotateFace_twice(0);
        char temp1[3]={};
        for(int i=0; i<3; i++) temp1[i]=cube[getIndex(4,0,2-i)];
        for(int i=0; i<3; i++) cube[getIndex(4,0,2-i)]=cube[getIndex(2,0,2-i)];
        for(int i=0; i<3; i++) cube[getIndex(2,0,2-i)]=temp1[i];
        char temp2[3]={};
        for(int i=0; i<3; i++) temp2[i]=cube[getIndex(1,0,2-i)];
        for(int i=0; i<3; i++) cube[getIndex(1,0,2-i)]=cube[getIndex(3,0,2-i)];
        for(int i=0; i<3; i++) cube[getIndex(3,0,2-i)]=temp2[i];
        return *this;
    }


    RubbixCube &d() override{
        this->rotateFace(5);
        char temp[3]={};
        for(int i=0; i<3; i++) temp[i]=cube[getIndex(4,2,i)];
        for(int i=0; i<3; i++) cube[getIndex(4,2,i)]=cube[getIndex(3,2,i)];
        for(int i=0; i<3; i++) cube[getIndex(3,2,i)]=cube[getIndex(2,2,i)];
        for(int i=0; i<3; i++) cube[getIndex(2,2,i)]=cube[getIndex(1,2,i)];
        for(int i=0; i<3; i++) cube[getIndex(1,2,i)]=temp[i];
        return *this;
    }

    RubbixCube &d_inv() override{
        this->rotateFace_inv(5);
        char temp[3]={};
        for(int i=0; i<3; i++) temp[i]=cube[getIndex(4,2,i)];
        for(int i=0; i<3; i++) cube[getIndex(4,2,i)]=cube[getIndex(1,2,i)];
        for(int i=0; i<3; i++) cube[getIndex(1,2,i)]=cube[getIndex(2,2,i)];
        for(int i=0; i<3; i++) cube[getIndex(2,2,i)]=cube[getIndex(3,2,i)];
        for(int i=0; i<3; i++) cube[getIndex(3,2,i)]=temp[i];
        return *this;
    }

    RubbixCube &d2() override{
        this->rotateFace_twice(5);
        char temp1[3]={};
        for(int i=0; i<3; i++) temp1[i]=cube[getIndex(4,2,i)];
        for(int i=0; i<3; i++) cube[getIndex(4,2,i)]=cube[getIndex(2,2,i)];
        for(int i=0; i<3; i++) cube[getIndex(2,2,i)]=temp1[i];
        char temp2[3]={};
        for(int i=0; i<3; i++) temp2[i]=cube[getIndex(1,2,i)];
        for(int i=0; i<3; i++) cube[getIndex(1,2,i)]=cube[getIndex(3,2,i)];
        for(int i=0; i<3; i++) cube[getIndex(3,2,i)]=temp2[i];
        return *this;
    }


    RubbixCube &l() override{
        this->rotateFace(1);
        char temp[3] = {};
        for(int i=0; i<3; i++) temp[i]=cube[getIndex(0,i,0)];
        for(int i=0; i<3; i++) cube[getIndex(0,i,0)]=cube[getIndex(4,2-i,2)];
        for(int i=0; i<3; i++) cube[getIndex(4,2-i,2)]=cube[getIndex(5,i,0)];
        for(int i=0; i<3; i++) cube[getIndex(5,i,0)]=cube[getIndex(2,i,0)];
        for(int i=0; i<3; i++) cube[getIndex(2,i,0)]=temp[i];
        return *this;
    }

    RubbixCube &l_inv() override{
        this->rotateFace_inv(1);
        char temp[3] = {};
        for(int i=0; i<3; i++) temp[i]=cube[getIndex(0,i,0)];
        for(int i=0; i<3; i++) cube[getIndex(0,i,0)]=cube[getIndex(2,i,0)];
        for(int i=0; i<3; i++) cube[getIndex(2,i,0)]=cube[getIndex(5,i,0)];
        for(int i=0; i<3; i++) cube[getIndex(5,i,0)]=cube[getIndex(4,2-i,2)];
        for(int i=0; i<3; i++) cube[getIndex(4,2-i,2)]=temp[i];
        return *this;
    }

    RubbixCube &l2() override{
        this->rotateFace_twice(1);
        char temp1[3]={};
        for(int i=0; i<3; i++) temp1[i]=cube[getIndex(0,i,0)];
        for(int i=0; i<3; i++) cube[getIndex(0,i,0)]=cube[getIndex(5,i,0)];
        for(int i=0; i<3; i++) cube[getIndex(5,i,0)]=temp1[i];
        char temp2[3]={};
        for(int i=0; i<3; i++) temp2[i]=cube[getIndex(4,2-i,2)];
        for(int i=0; i<3; i++) cube[getIndex(4,2-i,2)]=cube[getIndex(2,i,0)];
        for(int i=0; i<3; i++) cube[getIndex(2,i,0)]=temp2[i];
        return *this;
    }


    RubbixCube &r() override{
        this->rotateFace(3);
        char temp[3] = {};
        for(int i=0; i<3; i++) temp[i]=cube[getIndex(0,2-i,2)];
        for(int i=0; i<3; i++) cube[getIndex(0,2-i,2)]=cube[getIndex(2,2-i,2)];
        for(int i=0; i<3; i++) cube[getIndex(2,2-i,2)]=cube[getIndex(5,2-i,2)];
        for(int i=0; i<3; i++) cube[getIndex(5,2-i,2)]=cube[getIndex(4,i,0)];
        for(int i=0; i<3; i++) cube[getIndex(4,i,0)]=temp[i];
        return *this;
    }

    RubbixCube &r_inv() override{
        this->rotateFace_inv(3);
        char temp[3] = {};
        for(int i=0; i<3; i++) temp[i]=cube[getIndex(0,2-i,2)];
        for(int i=0; i<3; i++) cube[getIndex(0,2-i,2)]=cube[getIndex(4,i,0)];
        for(int i=0; i<3; i++) cube[getIndex(4,i,0)]=cube[getIndex(5,2-i,2)];
        for(int i=0; i<3; i++) cube[getIndex(5,2-i,2)]=cube[getIndex(2,2-i,2)];
        for(int i=0; i<3; i++) cube[getIndex(2,2-i,2)]=temp[i];
        return *this;
    }

    RubbixCube &r2() override{
        this->rotateFace_twice(3);
        char temp1[3]={};
        for(int i=0; i<3; i++) temp1[i]=cube[getIndex(0,2-i,2)];
        for(int i=0; i<3; i++) cube[getIndex(0,2-i,2)]=cube[getIndex(5,2-i,2)];
        for(int i=0; i<3; i++) cube[getIndex(5,2-i,2)]=temp1[i];
        char temp2[3]={};
        for(int i=0; i<3; i++) temp2[i]=cube[getIndex(4,i,0)];
        for(int i=0; i<3; i++) cube[getIndex(4,i,0)]=cube[getIndex(2,2-i,2)];
        for(int i=0; i<3; i++) cube[getIndex(2,2-i,2)]=temp2[i];
        return *this;
    }


    RubbixCube &f() override{
        this->rotateFace(2);
        char temp[3] = {};
        for(int i=0; i<3; i++) temp[i]=cube[getIndex(0,2,i)];
        for(int i=0; i<3; i++) cube[getIndex(0,2,i)]=cube[getIndex(1,2-i,2)];
        for(int i=0; i<3; i++) cube[getIndex(1,2-i,2)]=cube[getIndex(5,0,2-i)];
        for(int i=0; i<3; i++) cube[getIndex(5,0,2-i)]=cube[getIndex(3,i,0)];
        for(int i=0; i<3; i++) cube[getIndex(3,i,0)]=temp[i];
        return *this;
    }

    RubbixCube &f_inv() override{
        this->rotateFace_inv(2);
        char temp[3] = {};
        for(int i=0; i<3; i++) temp[i]=cube[getIndex(0,2,i)];
        for(int i=0; i<3; i++) cube[getIndex(0,2,i)]=cube[getIndex(3,i,0)];
        for(int i=0; i<3; i++) cube[getIndex(3,i,0)]=cube[getIndex(5,0,2-i)];
        for(int i=0; i<3; i++) cube[getIndex(5,0,2-i)]=cube[getIndex(1,2-i,2)];
        for(int i=0; i<3; i++) cube[getIndex(1,2-i,2)]=temp[i];
        return *this;
    }

    RubbixCube &f2() override{
        this->rotateFace_twice(2);
        char temp1[3]={};
        for(int i=0; i<3; i++) temp1[i]=cube[getIndex(0,2,i)];
        for(int i=0; i<3; i++) cube[getIndex(0,2,i)]=cube[getIndex(5,0,2-i)];
        for(int i=0; i<3; i++) cube[getIndex(5,0,2-i)]=temp1[i];
        char temp2[3]={};
        for(int i=0; i<3; i++) temp2[i]=cube[getIndex(3,i,0)];
        for(int i=0; i<3; i++) cube[getIndex(3,i,0)]=cube[getIndex(1,2-i,2)];
        for(int i=0; i<3; i++) cube[getIndex(1,2-i,2)]=temp2[i];
        return *this;
    }


    RubbixCube &b() override{
        this->rotateFace(4);
        char temp[3] = {};
        for(int i=0; i<3; i++) temp[i]=cube[getIndex(0,0,2-i)];
        for(int i=0; i<3; i++) cube[getIndex(0,0,2-i)]=cube[getIndex(3,2-i,2)];
        for(int i=0; i<3; i++) cube[getIndex(3,2-i,2)]=cube[getIndex(5,2,i)];
        for(int i=0; i<3; i++) cube[getIndex(5,2,i)]=cube[getIndex(1,i,0)];
        for(int i=0; i<3; i++) cube[getIndex(1,i,0)]=temp[i];
        return *this;
    }

    RubbixCube &b_inv() override{
        this->rotateFace_inv(4);
        char temp[3] = {};
        for(int i=0; i<3; i++) temp[i]=cube[getIndex(0,0,2-i)];
        for(int i=0; i<3; i++) cube[getIndex(0,0,2-i)]=cube[getIndex(1,i,0)];
        for(int i=0; i<3; i++) cube[getIndex(1,i,0)]=cube[getIndex(5,2,i)];
        for(int i=0; i<3; i++) cube[getIndex(5,2,i)]=cube[getIndex(3,2-i,2)];
        for(int i=0; i<3; i++) cube[getIndex(3,2-i,2)]=temp[i];
        return *this;
    }

    RubbixCube &b2() override{
        this->rotateFace_twice(4);
        char temp1[3]={};
        for(int i=0; i<3; i++) temp1[i]=cube[getIndex(0,0,2-i)];
        for(int i=0; i<3; i++) cube[getIndex(0,0,2-i)]=cube[getIndex(5,2,i)];
        for(int i=0; i<3; i++) cube[getIndex(5,2,i)]=temp1[i];
        char temp2[3]={};
        for(int i=0; i<3; i++) temp2[i]=cube[getIndex(1,i,0)];
        for(int i=0; i<3; i++) cube[getIndex(1,i,0)]=cube[getIndex(3,2-i,2)];
        for(int i=0; i<3; i++) cube[getIndex(3,2-i,2)]=temp2[i];
        return *this;
    }

    bool operator==(const RubbixCube1Darray &r1) const{
        for(int i=0; i<54; i++)
        if(r1.cube[i]!=cube[i])return false;
        return true;
    }

    RubbixCube1Darray &operator=(const RubbixCube1Darray &r1){
        for(int i=0; i<54; i++)
        cube[i]=r1.cube[i];
        return *this;
    }
};

struct Hash1D{
    size_t operator()(const RubbixCube1Darray &r1)const {
        string str="";
        for(int i=0; i<54; i++)str+=r1.cube[i];
    return hash<string>()(str);
    }
};