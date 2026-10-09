 #include "CornerPatternDatabase.h"

 CornerPatternDatabase::CornerPatternDatabase():PatternDatabase(88179840){}
 CornerPatternDatabase::CornerPatternDatabase(uint8_t init_val):PatternDatabase(88179840,init_val){}

 uint32_t CornerPatternDatabase::getDatabaseIndex(const RubbixCube &Cube) const{
    array<uint8_t,8> CornerPermu={
        Cube.getCornerIndex(0),
        Cube.getCornerIndex(1),
        Cube.getCornerIndex(2),
        Cube.getCornerIndex(3),
        Cube.getCornerIndex(4),
        Cube.getCornerIndex(5),
        Cube.getCornerIndex(6),
        Cube.getCornerIndex(7),
    };
    uint32_t rank =this->permuind.rank(CornerPermu);

    array<uint8_t,7>cornerOrientations ={
            Cube.getCornerOrientation(0),
            Cube.getCornerOrientation(1),
            Cube.getCornerOrientation(2),
            Cube.getCornerOrientation(3),
            Cube.getCornerOrientation(4),
            Cube.getCornerOrientation(5),
            Cube.getCornerOrientation(6),
    };
        uint32_t OrientationNum =
        cornerOrientations[0]*729+
        cornerOrientations[1]*243+
        cornerOrientations[2]*81+
        cornerOrientations[3]*27+
        cornerOrientations[4]*9+
        cornerOrientations[5]*3+
        cornerOrientations[6];

        return (rank*2187) + OrientationNum;
 }