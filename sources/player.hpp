#pragma once

#include <string>
#include <stack>
#include "card.hpp"


namespace ariel
{
    using namespace std;
    class Player
    {
    private:
        string pname; //name of the player.
        int cardst=0; // a variable number that counts the number of cards a player has won.
        stack<Card> player_cards; //stack of 26 cards for each player.
        string status; //status for each player.
        int numOfWin; //number of the wins for each player.
        int cardWon; //number of cards that player has won.
        int cardsLeft; //number of cards left in player's stack.


    public:
        Player(); //defult constructor.
        Player(string name); //constructor.
        int stacksize();
        int cardesTaken();
        //getters and setters.
        std:: string getName()const{
            return this->pname;
        }
        int getCardst() const{
            return this->cardst;
        }
        void setCardst(int num){
            this->cardst = cardst+num;
        }
        std::stack<Card>&get_player_cards(){
            return this->player_cards;
        }
        bool operator==(const Player& other) const{
            return pname==other.pname;
        }
        int getNumOfWin() const{
            return this->numOfWin;
        }
        void setNumOfWin(){
            this->numOfWin=this->getNumOfWin()+1;
        }
        string getStatus() const;
        void setStatus(int numofgame);

        
    };

}