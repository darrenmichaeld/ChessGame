// TASK 3: Implement the 4 Piece-derived classes here
// All classes will inherit the NamedPiece class 
// and implement the remaining pure virtual functions


// TODO 3.1: Leaper class
template <char N, int F, int R>
class Leaper : public NamedPiece<N>{
    private:

    public:
        Leaper(Color color):NamedPiece<N>(color){
        };

         Piece* clone() const {
            return new Leaper{*this};
        }

        BooleanMap getMoves(const Board& board) const {
            BooleanMap nm;
            Vector move;
            if (this->color == WHITE){
                move.file = F;
                move.rank = R;
            }
            else{
                move.file = -F;
                move.rank = -R; 
            }

            if(!board.piece(move + this->position)){
                nm.cell(move + this->position) = true;
            }
            else if (board.piece(move + this->position)->isOpponent(*this)){
                nm.cell(move + this->position) = true;
            }

            return nm;
        }
};


// // TODO 3.2: Rider class
template <char N, int F, int R, int RANGE>
class Rider: public NamedPiece<N>{
    private:
    public:
        Rider(Color color): NamedPiece<N>(color){
        };

        Piece* clone() const {
            return new Rider{*this};
        }

        BooleanMap getMoves(const Board& board) const
        {
            Vector move;
            BooleanMap ridermap;
            if (this->color == WHITE){
                move.file = F;
                move.rank = R;
            }
            else{
                move.file = -F;
                move.rank = -R; 
            }
            for(int i = 1; i <= RANGE; i++)
            {
                Position newposition = this->position;
                Vector moves = move * i;
                newposition = moves + newposition;
                if(board.piece(newposition) == nullptr)
                {
                    ridermap.cell(newposition) = true;
                    
                }
                else if(board.piece(newposition)->isOpponent(*this))
                {
                    ridermap.cell(newposition) = true;
                    break;
                }
                else if(board.piece(newposition)->isOpponent(*this) == false)
                {
                    break;
                }
            }
            
            return ridermap;
            }
};


// // TODO 3.3: Compound class
template <char N, typename P1, typename P2>
class Compound: public NamedPiece<N>{
    private:
    public:
        Compound(Color color):NamedPiece<N>(color){
        }

        Piece* clone() const {
            return new Compound(*this);
        }

        BooleanMap getMoves(const Board& board) const
        {
            P1 p1(this->color);
            P2 p2(this->color);

            p1.setPosition(this->position);
            p2.setPosition(this->position);

            BooleanMap b1 = p1.getMoves(board.getTempBoard(p1.clone(), this->position));
            BooleanMap b2 = p2.getMoves(board.getTempBoard(p2.clone(), this->position));

            b1 |= b2;
            return b1;
        }
};


// // TODO 3.4: Divergent class
template <char N, typename M, typename C>
class Divergent: public NamedPiece<N>{
    private:
    public:
        Divergent(Color color):NamedPiece<N>(color){
        }

        Piece* clone() const {
            return new Divergent(*this);
        }

        BooleanMap getMoves(const Board& board) const
        {
            M p1(this->color);
            C p2(this->color);

            p1.setPosition(this->position);
            p2.setPosition(this->position);

            BooleanMap b1 = p1.getMoves(board.getTempBoard(p1.clone(), p1.getPosition()));
            BooleanMap b2 = p2.getMoves(board.getTempBoard(p2.clone(), p2.getPosition()));

            BooleanMap enemypos = board.getOpponentMap(this->color);
            BooleanMap notenemypos = ~enemypos;
            b2 &= enemypos;
            
            b1 &= notenemypos;
     
            b1 |= b2;
            return b1;
        }
};
