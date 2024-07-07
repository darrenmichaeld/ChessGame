#include <iostream>
#include "board.h"
#include "piece.h"
using namespace std;

/**
 * TASK 2.1: Board copy constructor
*/
Board::Board(const Board& board)
{
    // TODO
    // Piece clone
    for(int i = 0; i < NUM_FILES; i++){
        for(int j = 0; j < NUM_RANKS; j++){
            if(board.pieces[i][j] != nullptr){         
                this->pieces[i][j] = board.pieces[i][j]->clone();
            }
            else{
                this->pieces[i][j] = nullptr;
            }

        }
    }
    
    // isWhiteTurn
    this->isWhiteTurn = board.isWhiteTurn;

    // selectedPiece
    if(board.selectedPiece)
    {
        this->selectedPiece = piece(board.selectedPiece->getPosition());
    }
    else{
        this->selectedPiece = nullptr;
    }

    // moveMap
    this->moveMap = board.moveMap;

    // royalPieces
    for(int i = 0; i < 2 ;i++)
    {
        if(board.royalPieces[i] != nullptr){
            this->royalPieces[i] = piece(board.royalPieces[i]->getPosition());
        }  
        else{
            this->royalPieces[i] = nullptr;
        }
    }
}

/**
 * TASK 2.2: Board destructor
*/
Board::~Board() 
{
    // TODO
    // delete pieces
    for(int i = 0; i < NUM_FILES; i++){
       for(int j = 0; j < NUM_RANKS ; j++){
            if(this->pieces[i][j] != nullptr)
            {
                delete this->pieces[i][j];
                this->pieces[i][j] = nullptr;
            }
       }
    }   
}


/**
 * TASK 4.1: Board::move(const Position&)
*/
void Board::move(const Position& destPos)
{
    // Safeguard against misusage of move()
    if (!selectedPiece) {
        cout << "ERROR: Piece not selected, cannot call move()" << endl;
        return;
    }

    // TODO
        Position now;
        now.file = selectedPiece->getPosition().file;
        now.rank = selectedPiece->getPosition().rank;

        if (this->piece(destPos) != nullptr){
            delete this->piece(destPos);
            this->piece(destPos) = nullptr;
        }

        this->piece(now) = nullptr;
        this->piece(destPos) = selectedPiece;
        selectedPiece->setPosition(destPos);
        isWhiteTurn = !isWhiteTurn;
        return;
    }
    


/**
 * TASK 4.2: Board::getAttackingMap() const
*/
BooleanMap Board::getAttackingMap() const
{
    // TODO
    BooleanMap attackmap{};
    for(int i = 0; i < NUM_FILES; i++){
        for(int j = 0; j < NUM_RANKS; j++){
            if(piece(static_cast<_FILE>(i),static_cast<_RANK>(j)) != nullptr && piece(static_cast<_FILE>(i), static_cast<_RANK>(j))->isWhite() == isWhiteTurn){
                BooleanMap OpponentMap = this->getOpponentMap(isWhiteTurn);
                BooleanMap piecemap = this->piece(static_cast<_FILE>(i),static_cast<_RANK>(j))->getMoves(*this);
                piecemap &= OpponentMap;
                attackmap |= piecemap;
            }
        }
    }
    return attackmap;
}

/**
 * TASK 4.3: Board::validateMoveMap()
*/
void Board::validateMoveMap()
{
    // TODO
    for(int i = 0; i < NUM_FILES; i++){
        for (int j=0 ;j < NUM_RANKS; j++){
            Position position{static_cast<_FILE>(i),static_cast<_RANK>(j)};
            if (moveMap.cell(position.file, position.rank) && royalPieces[isWhiteTurn] != nullptr){
                Board temp_board(*this);
                Piece* royal_temp = temp_board.royalPieces[isWhiteTurn];
                temp_board.move(position);
                BooleanMap validate_map = temp_board.getAttackingMap();

                if (isRoyal(selectedPiece)){
                    if(validate_map.cell(temp_board.selectedPiece->getPosition())){
                        moveMap.cell(position) = false;
                    }
                }

                else{
                    if(validate_map.cell(royal_temp->getPosition())){
                        moveMap.cell(position) = false;
                    }
                }
            }
        }
    }    
}

