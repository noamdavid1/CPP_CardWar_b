#include "player.hpp"
#include "card.hpp"
#include <stack>

namespace ariel
{
    // stack<Card> player_cards;
    Player::Player(){};

    Player::Player(string name) // initialization of the constructor.
    {
        this->pname = name;
    };
    // prints the amount of cards left.
    int Player::stacksize()
    {
        return (this->get_player_cards()).size();
    }
    // prints the amount of cards this player has won.
    int Player::cardesTaken()
    {
        return this->getCardst();
    }
    //get the status of each player.
    string Player::getStatus() const
    {
        return this->status;
    }
    //set the status of each player.
    void Player::setStatus(int numofgame)
    {
        double winRate = (this->getNumOfWin() * 100 / numofgame);
        int amountOfDraws = (26 - this->cardsLeft);
        double DrawRate = ((100 * amountOfDraws) / numofgame);
        this->cardWon = this->cardesTaken();
        this->cardsLeft = this->stacksize();
        this->status = this->pname + ": win rate:" + std::to_string(winRate) + " ,card won:" + std::to_string(cardWon) + " ,cards left:" + std::to_string(cardsLeft) + " ,amount of draws:" + std::to_string(amountOfDraws) + " ,draw rate:" + std::to_string(DrawRate);
    }
}