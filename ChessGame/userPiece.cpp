#include "userPiece.h"

// TASK 4.2: isRoyal(const Piece*)
// TODO
bool isRoyal(const Piece* piece){
    if (typeid(*piece) == typeid(King)){
        return true;
    }
    return false;
}

// TASK 4.3: Implement any Pawn function(s) here if needed

Piece* Pawn::clone() const{
        return new Pawn{*this};
    }

BooleanMap Pawn::getMoves(const Board& board) const{
    BooleanMap before = Divergent::getMoves(board);
        if (this->getColor() == true && this->position.rank == 1){
            if(board.piece(this->position.file, _4) == nullptr){
                BooleanMap nm;
                Vector move;
                move.file = _A;
                move.rank = _3;
                Position now = move + this->position;
                
                nm.cell(now.file,now.rank) = true;
                before |= nm;
                
            }
        }
        else if(this->getColor() == false && this->position.rank == 6){
            if(board.piece(this->position.file, _5) == nullptr){
                BooleanMap nm;
                Vector move;
                move.file = _A;
                move.rank = _3;
                move = move * -1;
                Position now = move + this->position;

                nm.cell(now.file,now.rank) = true;
                before |= nm;
                
            }
        }
        return before;
    }
