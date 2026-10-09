#include "RubbixCube.h"

char RubbixCube::getColorLetter(Color color){
    switch (color){
    case Color::Blue:
        return 'B';
    case Color::Green:
        return 'G';
    case Color::Orange:
        return 'O';
    case Color::Red:
        return 'R';
    case Color::Yellow:
        return 'Y';
    case Color::White:
        return 'W';
    default:
        return ' ';
    }
}

string RubbixCube::getMove(Move ind){
    switch (ind){
    case Move::l1:
        return "L";
    case Move::l_inv:
        return "L'";
    case Move::l2:
        return "L2";
    case Move::r1:
        return "R";
    case Move::r_inv:
        return "R'";
    case Move::r2:
        return "R2";
    case Move::u1:
        return "U";
    case Move::u_inv:
        return "U'";
    case Move::u2:
        return "U2";
    case Move::d1:
        return "D";
    case Move::d_inv:
        return "D'";
    case Move::d2:
        return "D2";
    case Move::f1:
        return "F";
    case Move::f_inv:
        return "F'";
    case Move::f2:
        return "F2";
    case Move::b1:
        return "B";
    case Move::b_inv:
        return "B'";
    case Move::b2:
        return "B2";
    }
}

RubbixCube &RubbixCube::move(Move ind){
    switch (ind){
    case Move::l1:
        return this->l();
    case Move::l_inv:
        return this->l_inv();
    case Move::l2:
        return this->l2();
    case Move::r1:
        return this->r();
    case Move::r_inv:
        return this->r_inv();
    case Move::r2:
        return this->r2();
    case Move::u1:
        return this->u();
    case Move::u_inv:
        return this->u_inv();
    case Move::u2:
        return this->u2();
    case Move::d1:
        return this->d();
    case Move::d_inv:
        return this->d_inv();
    case Move::d2:
        return this->d2();
    case Move::f1:
        return this->f();
    case Move::f_inv:
        return this->f_inv();
    case Move::f2:
        return this->f2();
    case Move::b1:
        return this->b();
    case Move::b_inv:
        return this->b_inv();
    case Move::b2:
        return this->b2();
    }
}

RubbixCube &RubbixCube::invert(Move ind){
    switch (ind){
    case Move::l1:
        return this->l_inv();
    case Move::l_inv:
        return this->l();
    case Move::l2:
        return this->l2();
    case Move::r1:
        return this->r_inv();
    case Move::r_inv:
        return this->r();
    case Move::r2:
        return this->r2();
    case Move::u1:
        return this->u_inv();
    case Move::u_inv:
        return this->u();
    case Move::u2:
        return this->u2();
    case Move::d1:
        return this->d_inv();
    case Move::d_inv:
        return this->d();
    case Move::d2:
        return this->d2();
    case Move::f1:
        return this->f_inv();
    case Move::f_inv:
        return this->f();
    case Move::f2:
        return this->f2();
    case Move::b1:
        return this->b_inv();
    case Move::b_inv:
        return this->b();
    case Move::b2:
        return this->b2();
    }
}

void RubbixCube::print() const{
    cout<<"Rubbix Cube :\n";
    for(int row=0; row<3; row++){
        cout<<"       ";
        for(int col=0; col<3; col++){
            cout<<getColorLetter(getColor(Face::Up,row,col))<<" ";   
        }
        cout<<"\n";
    }
    cout<<"\n";

    for(int row=0; row<3; row++){
        for(int col=0; col<3; col++){
            cout<<getColorLetter(getColor(Face::Left,row,col))<<" ";
        }
        cout<<" ";
        for(int col=0; col<3; col++){
            cout<<getColorLetter(getColor(Face::Front,row,col))<<" ";
        }
        cout<<" ";
        for(int col=0; col<3; col++){
            cout<<getColorLetter(getColor(Face::Right,row,col))<<" ";
        }
        cout<<" ";
        for(int col=0; col<3; col++){
            cout<<getColorLetter(getColor(Face::Back,row,col))<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";

    for(int row=0; row<3; row++){
        for(unsigned i=0; i<7; i++) cout<<" ";
        for(int col=0; col<3; col++){
            cout<<getColorLetter(getColor(Face::Down,row,col))<<" ";   
        }
        cout<<"\n";
    }
    cout<<"\n";

}

vector<RubbixCube::Move> RubbixCube::RandomShuffleCube(unsigned int times){
    vector<Move> movePerfomed;
    srand(time(0));
    for(unsigned int i=0; i<times; i++){
        unsigned int selectMove= rand()%18;
        movePerfomed.push_back(static_cast<Move>(selectMove));
        this->move(static_cast<Move>(selectMove));
    }
    return movePerfomed;
}

string RubbixCube::getCornerColorString(uint8_t ind) const{
    string str="";
 /*
     *         3_ _ _ _ _ 2
     *       / |        / |
     *      0__|_______1  |
     *      |  |       |  |
     *      |  7 _ _ _ |_ 6
     *      | /        | /
     *      5__________4
*/
    switch (ind){
        //UFR
    case 0:
        str+=getColorLetter(getColor(Face::Up,2,2)); 
        str+=getColorLetter(getColor(Face::Front,0,2)); 
        str+=getColorLetter(getColor(Face::Right,0,0)); 
        break; 
        //UFL
    case 1:
        str+=getColorLetter(getColor(Face::Up,2,0)); 
        str+=getColorLetter(getColor(Face::Front,0,0)); 
        str+=getColorLetter(getColor(Face::Left,0,2)); 
        break;
        //UBL
    case 2:
        str+=getColorLetter(getColor(Face::Up,0,0)); 
        str+=getColorLetter(getColor(Face::Back,0,2)); 
        str+=getColorLetter(getColor(Face::Left,0,0)); 
        break;
        //UBR
    case 3:
        str+=getColorLetter(getColor(Face::Up,0,2)); 
        str+=getColorLetter(getColor(Face::Back,0,0)); 
        str+=getColorLetter(getColor(Face::Right,0,2)); 
        break; 
        //DFR
    case 4:
        str+=getColorLetter(getColor(Face::Down,0,2)); 
        str+=getColorLetter(getColor(Face::Front,2,2)); 
        str+=getColorLetter(getColor(Face::Right,2,0)); 
        break; 
        //DFL
    case 5:
        str+=getColorLetter(getColor(Face::Down,0,0)); 
        str+=getColorLetter(getColor(Face::Front,2,0)); 
        str+=getColorLetter(getColor(Face::Left,2,2)); 
        break;   
        //DBR
    case 6:
        str+=getColorLetter(getColor(Face::Down,2,2)); 
        str+=getColorLetter(getColor(Face::Back,2,0)); 
        str+=getColorLetter(getColor(Face::Right,2,2)); 
        break;  
        //DBL
    case 7:
        str+=getColorLetter(getColor(Face::Down,2,0)); 
        str+=getColorLetter(getColor(Face::Back,2,2)); 
        str+=getColorLetter(getColor(Face::Left,2,0)); 
        break;
    }
    return str;
}

uint8_t RubbixCube::getCornerIndex(uint8_t ind) const{
    string corner= getCornerColorString(ind);
    uint8_t ret=0;
    for (auto c : corner) {
        if (c == 'Y') ret |= (1 << 2);
        if (c == 'O') ret |= (1 << 1);
        if (c == 'G') ret |= (1 << 0);
    }
    return ret;
}

uint8_t RubbixCube::getCornerOrientation(uint8_t ind) const{
    string corner = getCornerColorString(ind);
    string actual_str="";
    for(auto c: corner){
        if(c!='W' && c!='Y')continue;
        actual_str.push_back(c);
    }
    if(corner[1]==actual_str[0]){
        return 1;
    }else if(corner[2]==actual_str[0]){
        return 2;
    }else return 0;
}