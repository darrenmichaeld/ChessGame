#include <iostream>
#include "utility.h"
using namespace std;

ostream& operator<<(ostream& os, const Position& pos)
{
    os << static_cast<char>(pos.file + 'a') << static_cast<char>(pos.rank + '1');
    return os;
}

// TASK 1: Implement the 6 operator overloading functions of Position, Vector and BooleanMap
// You need to write the full function prototypes and implementations


// TODO 1.1: Position::operator==(const Position&) const
bool Position::operator==(const Position& pos) const{
    if(this->file == pos.file && this->rank == pos.rank){
        return true;
    }
    else{
        return false;
    }
}

// TODO 1.2: Vector::operator+(const Position&) const
Position Vector::operator+(const Position& pos) const{
    int newfile = static_cast<int>(this->file) + static_cast<int>(pos.file);
    int newrank = static_cast<int>(this->rank) + static_cast<int>(pos.rank);
    if(newfile < 8 && newrank < 8 && newfile >= 0 && newrank >= 0){
        _FILE newFfile = static_cast<_FILE>(newfile);
        _RANK newRrank = static_cast<_RANK>(newrank);
        return Position {newFfile, newRrank};
    }
    else{
        return pos;
    }
}


// TODO 1.3: Vector::operator*(int) const
Vector Vector::operator*(int mul) const{
    int newfile = static_cast<int>(this->file);
    int newrank = static_cast<int>(this->rank);
    newfile = newfile * mul;
    newrank = newrank * mul;
    _FILE newFfile = static_cast<_FILE>(newfile);
    _RANK newRrank = static_cast<_RANK>(newrank);
    return Vector {newFfile, newRrank};
}

// TODO 1.4: BooleanMap::operator|=(const BooleanMap&)
BooleanMap& BooleanMap::operator|=(const BooleanMap& other){
    for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(this->cells[i][j] == true ||other.cells[i][j] == true){
                    this->cells[i][j] = true;
                }
            }
        }
    return *this;
}

// TODO 1.5: BooleanMap::operator&=(const BooleanMap&)
BooleanMap& BooleanMap::operator&=(const BooleanMap& other){
    for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(this->cells[i][j] == true && other.cells[i][j] == true){
                    this->cells[i][j] = true;
                }
                else{
                    this->cells[i][j] = false;
                }
            }
        }
    return *this;
}


// TODO 1.6: BooleanMap::operator~() const
BooleanMap BooleanMap::operator~() const{
    BooleanMap newmap;
    for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(this->cells[i][j]){
                    newmap.cells[i][j] = false;
                }
                else if(!this->cells[i][j])
                {
                    newmap.cells[i][j] = true;
                }
            }
        }
    return newmap;
}
