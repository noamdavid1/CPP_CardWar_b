#pragma once

namespace ariel
{
    class Card
    {
    private:
        int rank; //the number(rank) of the card.
        char shape; //shape that drawn on the card.   
    public:
        Card();
        Card(int rank,char shape);
        int getRank()const{
            return this->rank;
        }
        char getShape() const{
            return this->shape;
        }
    };
}