 #include "PatternDatabase.h"
 using namespace std;

 PatternDatabase::PatternDatabase(const size_t size):
    Database(size, 0xFF), size(size), numItems(0){}

 PatternDatabase::PatternDatabase(const size_t size, uint8_t init_val):
    Database(size, init_val), size(size), numItems(0){}

//if the index is already set, it does nothing and return false
//else it sets ind and return true

bool PatternDatabase::setNumMoves(const uint32_t ind,const uint8_t numMoves){
    uint8_t oldMoves =this->getNumMoves(ind);

//New item is getting added
    if(oldMoves==0xF){
        ++this->numItems;
    }
    if(oldMoves> numMoves){
        this->Database.set(ind,numMoves);
        return true;
    }
    return false;
}

bool PatternDatabase::setNumMoves(const RubbixCube &Cube, const uint8_t numMoves){
    return this->setNumMoves(this->getNumMoves(Cube),numMoves);
}

uint8_t PatternDatabase::getNumMoves(const uint32_t ind) const{
    return this->Database.get(ind);
}

uint8_t PatternDatabase::getNumMoves(const RubbixCube &Cube) const{
    return this->getNumMoves(this->getDatabaseIndex(Cube));
}

size_t PatternDatabase::getSize() const{
    return this->size;
}

size_t PatternDatabase::getNumsItems() const{
    return this->numItems;
}

bool PatternDatabase::isFull() const{
    return this->numItems == this->size;
}

void PatternDatabase ::toFile(const string &filePath) const{

    ofstream writer(filePath,ios::out| ios::binary |ios::trunc);
    if(!writer.is_open())
        throw "Failed to open the fileto write";

    writer.write(
        reinterpret_cast<const char*>(this->Database.data()),
        this->Database.storageSize()
    );
    writer.close();
}

//return true of databaseis loaded succesfully
// else return false

bool PatternDatabase::fromFile(const string &filePath){
    ifstream reader(filePath, ios::in | ios::binary | ios::ate);

    if(!reader.is_open()) return false;

    size_t fileSize = reader.tellg();
    if(fileSize < this->Database.storageSize()){
        reader.close();
        throw "Database corrupt! File is smaller than expected storage size";
    }

    reader.seekg(0, ios::beg);
    reader.read(
        reinterpret_cast<char*>(this->Database.data()),
        this->Database.storageSize()
    );
    reader.close();
    this->numItems= this->size;
    return true;
}

vector<uint8_t>PatternDatabase::inflate()const{
    vector<uint8_t> inflated;
    this->Database.inflate(inflated);
    return inflated;
}

void PatternDatabase::reset(){
    if(this->numItems != 0){
        this->Database.reset(0xFF);
        this->numItems=0;
    }
}