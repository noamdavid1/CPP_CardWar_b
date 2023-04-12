#include "card.hpp"

namespace ariel
{

    Card::Card(){};
    Card::Card(int rank,char shape){
        this->rank=rank;
        this->shape=shape;
    }
}
