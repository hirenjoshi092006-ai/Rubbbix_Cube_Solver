#include "RubbixCube.h"
class RubbixCube3Darray : public RubbixCube{
    private:
    //Helper function
    void rotateFace(int ind){
        char temp[3][3]={};
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                temp[i][j]=cube[ind][i][j];
            }
        }
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cube[ind][j][2-i]=temp[i][j];
            }
        }
    }
    void rotateFace_inv(int ind){
         char temp[3][3]={};
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                temp[i][j]=cube[ind][i][j];
            }
        }
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cube[ind][2-j][i]=temp[i][j];
            }
        }
    }
    void rotateFace_twice(int ind){
         char temp[3][3]={};
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                temp[i][j]=cube[ind][i][j];
            }
        }
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cube[ind][j][i]=temp[i][j];
            }
        }
    }
    public:
    //      0
    //  1   2   3   4
    //      5
    char cube[6][3][3];

    //constructor
    RubbixCube3Darray(){
        for(int i=0; i<6; i++){
            for(int j=0; j<3; j++){
                for(int k=0; k<3; k++){
                    cube[i][j][k]=getColorLetter(Color(i));
                }
            }
        }
    }

    bool isSolved() const override{
        for(int i=0; i<6; i++){
            for(int j=0; j<3; j++){
                for(int k=0; k<3; k++){
                    if(this->cube[i][j][k]==getColorLetter(Color(i))) continue;
                    return false;
                }
            }
        }
        return true;
    }

    Color getColor(Face face, unsigned row, unsigned col) const override{
        char color=cube[int(face)][row][col];
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
        cube[int(face)][row][col] = getColorLetter(color);
    }

    RubbixCube &u() override{
        this->rotateFace(0);
        char temp[3]={};
        for(int i=0; i<3; i++) temp[i]=cube[4][0][2-i];
        for(int i=0; i<3; i++) cube[4][0][2-i]=cube[1][0][2-i];
        for(int i=0; i<3; i++) cube[1][0][2-i]=cube[2][0][2-i];
        for(int i=0; i<3; i++) cube[2][0][2-i]=cube[3][0][2-i];
        for(int i=0; i<3; i++) cube[3][0][2-i]=temp[i];
        return *this;
    }

    RubbixCube &u_inv() override{
        this->rotateFace_inv(0);
        char temp[3]={};
        for(int i=0; i<3; i++) temp[i]=cube[4][0][2-i];
        for(int i=0; i<3; i++) cube[4][0][2-i]=cube[3][0][2-i];
        for(int i=0; i<3; i++) cube[3][0][2-i]=cube[2][0][2-i];
        for(int i=0; i<3; i++) cube[2][0][2-i]=cube[1][0][2-i];
        for(int i=0; i<3; i++) cube[1][0][2-i]=temp[i];
        return *this;
    }

    RubbixCube &u2() override{
        this->rotateFace_twice(0);
        char temp1[3]={};
        for(int i=0; i<3; i++) temp1[i]=cube[4][0][2-i];
        for(int i=0; i<3; i++) cube[4][0][2-i]=cube[2][0][2-i];
        for(int i=0; i<3; i++) cube[2][0][2-i]=temp1[i];
        char temp2[3]={};
        for(int i=0; i<3; i++) temp2[i]=cube[1][0][2-i];
        for(int i=0; i<3; i++) cube[1][0][2-i]=cube[3][0][2-i];
        for(int i=0; i<3; i++) cube[3][0][2-i]=temp2[i];
        return *this;
    }

    RubbixCube &d() override{
        this->rotateFace(5);
        char temp[3]={};
        for(int i=0; i<3; i++) temp[i]=cube[4][2][i];
        for(int i=0; i<3; i++) cube[4][2][i]=cube[3][2][i];
        for(int i=0; i<3; i++) cube[3][2][i]=cube[2][2][i];
        for(int i=0; i<3; i++) cube[2][2][i]=cube[1][2][i];
        for(int i=0; i<3; i++) cube[1][2][i]=temp[i];
        return *this;
    }

    RubbixCube &d_inv() override{
        this->rotateFace_inv(5);
        char temp[3]={};
        for(int i=0; i<3; i++) temp[i]=cube[4][2][i];
        for(int i=0; i<3; i++) cube[4][2][i]=cube[1][2][i];
        for(int i=0; i<3; i++) cube[1][2][i]=cube[2][2][i];
        for(int i=0; i<3; i++) cube[2][2][i]=cube[3][2][i];
        for(int i=0; i<3; i++) cube[3][2][i]=temp[i];
        return *this;
    }

    RubbixCube &d2() override{
        this->rotateFace_twice(5);
        char temp1[3]={};
        for(int i=0; i<3; i++) temp1[i]=cube[4][2][i];
        for(int i=0; i<3; i++) cube[4][2][i]=cube[2][2][i];
        for(int i=0; i<3; i++) cube[2][2][i]=temp1[i];
        char temp2[3]={};
        for(int i=0; i<3; i++) temp2[i]=cube[1][2][i];
        for(int i=0; i<3; i++) cube[1][2][i]=cube[3][2][i];
        for(int i=0; i<3; i++) cube[3][2][i]=temp2[i];
        return *this;
    }


    RubbixCube &l() override{
        this->rotateFace(1);
        char temp[3] = {};
        for(int i=0; i<3; i++) temp[i]=cube[0][i][0];
        for(int i=0; i<3; i++) cube[0][i][0]=cube[4][2-i][2];
        for(int i=0; i<3; i++) cube[4][2-i][2]=cube[5][i][0];
        for(int i=0; i<3; i++) cube[5][i][0]=cube[2][i][0];
        for(int i=0; i<3; i++) cube[2][i][0]=temp[i];
        return *this;
    }

    RubbixCube &l_inv() override{
        this->rotateFace_inv(1);
        char temp[3] = {};
        for(int i=0; i<3; i++) temp[i]=cube[0][i][0];
        for(int i=0; i<3; i++) cube[0][i][0]=cube[2][i][0];
        for(int i=0; i<3; i++) cube[2][i][0]=cube[5][i][0];
        for(int i=0; i<3; i++) cube[5][i][0]=cube[4][2-i][2];
        for(int i=0; i<3; i++) cube[4][2-i][2]=temp[i];
        return *this;
    }

    RubbixCube &l2() override{
        this->rotateFace_twice(1);
        char temp1[3]={};
        for(int i=0; i<3; i++) temp1[i]=cube[0][i][0];
        for(int i=0; i<3; i++) cube[0][i][0]=cube[5][i][0];
        for(int i=0; i<3; i++) cube[5][i][0]=temp1[i];
        char temp2[3]={};
        for(int i=0; i<3; i++) temp2[i]=cube[4][2-i][2];
        for(int i=0; i<3; i++) cube[4][2-i][2]=cube[2][i][0];
        for(int i=0; i<3; i++) cube[2][i][0]=temp2[i];
        return *this;
    }


    RubbixCube &r() override{
        this->rotateFace(3);
        char temp[3] = {};
        for(int i=0; i<3; i++) temp[i]=cube[0][2-i][2];
        for(int i=0; i<3; i++) cube[0][2-i][2]=cube[2][2-i][2];
        for(int i=0; i<3; i++) cube[2][2-i][2]=cube[5][2-i][2];
        for(int i=0; i<3; i++) cube[5][2-i][2]=cube[4][i][0];
        for(int i=0; i<3; i++) cube[4][i][0]=temp[i];
        return *this;
    }

    RubbixCube &r_inv() override{
        this->rotateFace_inv(3);
        char temp[3] = {};
        for(int i=0; i<3; i++) temp[i]=cube[0][2-i][2];
        for(int i=0; i<3; i++) cube[0][2-i][2]=cube[4][i][0];
        for(int i=0; i<3; i++) cube[4][i][0]=cube[5][2-i][2];
        for(int i=0; i<3; i++) cube[5][2-i][2]=cube[2][2-i][2];
        for(int i=0; i<3; i++) cube[2][2-i][2]=temp[i];
        return *this;
    }

    RubbixCube &r2() override{
        this->rotateFace_twice(3);
        char temp1[3]={};
        for(int i=0; i<3; i++) temp1[i]=cube[0][2-i][2];
        for(int i=0; i<3; i++) cube[0][2-i][2]=cube[5][2-i][2];
        for(int i=0; i<3; i++) cube[5][2-i][2]=temp1[i];
        char temp2[3]={};
        for(int i=0; i<3; i++) temp2[i]=cube[4][i][0];
        for(int i=0; i<3; i++) cube[4][i][0]=cube[2][2-i][2];
        for(int i=0; i<3; i++) cube[2][2-i][2]=temp2[i];
        return *this;
    }


    RubbixCube &f() override{
        this->rotateFace(2);
        char temp[3] = {};
        for(int i=0; i<3; i++) temp[i]=cube[0][2][i];
        for(int i=0; i<3; i++) cube[0][2][i]=cube[1][2-i][2];
        for(int i=0; i<3; i++) cube[1][2-i][2]=cube[5][0][2-i];
        for(int i=0; i<3; i++) cube[5][0][2-i]=cube[3][i][0];
        for(int i=0; i<3; i++) cube[3][i][0]=temp[i];
        return *this;
    }

    RubbixCube &f_inv() override{
        this->rotateFace_inv(2);
        char temp[3] = {};
        for(int i=0; i<3; i++) temp[i]=cube[0][2][i];
        for(int i=0; i<3; i++) cube[0][2][i]=cube[3][i][0];
        for(int i=0; i<3; i++) cube[3][i][0]=cube[5][0][2-i];
        for(int i=0; i<3; i++) cube[5][0][2-i]=cube[1][2-i][2];
        for(int i=0; i<3; i++) cube[1][2-i][2]=temp[i];
        return *this;
    }

    RubbixCube &f2() override{
        this->rotateFace_twice(2);
        char temp1[3]={};
        for(int i=0; i<3; i++) temp1[i]=cube[0][2][i];
        for(int i=0; i<3; i++) cube[0][2][i]=cube[5][0][2-i];
        for(int i=0; i<3; i++) cube[5][0][2-i]=temp1[i];
        char temp2[3]={};
        for(int i=0; i<3; i++) temp2[i]=cube[3][i][0];
        for(int i=0; i<3; i++) cube[3][i][0]=cube[1][2-i][2];
        for(int i=0; i<3; i++) cube[1][2-i][2]=temp2[i];
        return *this;
    }

    RubbixCube &b() override{
        this->rotateFace(4);
        char temp[3] = {};
        for(int i=0; i<3; i++) temp[i]=cube[0][0][2-i];
        for(int i=0; i<3; i++) cube[0][0][2-i]=cube[3][2-i][2];
        for(int i=0; i<3; i++) cube[3][2-i][2]=cube[5][2][i];
        for(int i=0; i<3; i++) cube[5][2][i]=cube[1][i][0];
        for(int i=0; i<3; i++) cube[1][i][0]=temp[i];

        return *this;
    }

    RubbixCube &b_inv() override{
        this->rotateFace_inv(4);
        char temp[3] = {};
        for(int i=0; i<3; i++) temp[i]=cube[0][0][2-i];
        for(int i=0; i<3; i++) cube[0][0][2-i]=cube[1][i][0];
        for(int i=0; i<3; i++) cube[1][i][0]=cube[5][2][i];
        for(int i=0; i<3; i++) cube[5][2][i]=cube[3][2-i][2];
        for(int i=0; i<3; i++) cube[3][2-i][2]=temp[i];
        return *this;
    }

    RubbixCube &b2() override{
        this->rotateFace_twice(4);
        char temp1[3]={};
        for(int i=0; i<3; i++) temp1[i]=cube[0][0][2-i];
        for(int i=0; i<3; i++) cube[0][0][2-i]=cube[5][2][i];
        for(int i=0; i<3; i++) cube[5][2][i]=temp1[i];
        char temp2[3]={};
        for(int i=0; i<3; i++) temp2[i]=cube[1][i][0];
        for(int i=0; i<3; i++) cube[1][i][0]=cube[3][2-i][2];
        for(int i=0; i<3; i++) cube[3][2-i][2]=temp2[i];
        return *this;
    }


    bool operator==(const RubbixCube3Darray &r1) const{
        for(int i=0; i<6; i++){
            for(int j=0; j<3; j++){
                for(int k=0; k<3; k++){
                    if(r1.cube[i][j][k]!=cube[i][j][k])return false;
                }
            }
        }
        return true;
    }

    RubbixCube3Darray &operator=(const RubbixCube3Darray &r1){
        for(int i=0; i<6; i++){
            for(int j=0; j<3; j++){
                for(int k=0; k<3; k++){
                    cube[i][j][k]=r1.cube[i][j][k];
                }
            }
        }
        return *this;
    }
};

struct Hash3D{
    size_t operator()(const RubbixCube3Darray &r1)const {
        string str="";
        for(int i=0; i<6; i++){
            for(int j=0; j<3; j++){
                for(int k=0; k<3; k++){
                    str+=r1.cube[i][j][k];
                }
            }
        }
    return hash<string>()(str);
    }
};