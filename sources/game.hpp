#pragma once

#include "player.hpp"
#include "card.hpp"
#include <vector>
#include <iostream>


namespace ariel
{
    class Game
    {
    private:
        Player &player_a;
        Player &player_b;
        std::vector<Card> cards; //the pack of all 52 cards
        std::stack<string> turns; //stack of documentation of each turn.
        bool winner; //when the game over there is a winner.
        int numofgame; //counting the turns.

    public:
        Game(Player &playera, Player &playerb); // constructor.
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
        void initialize_cards();
        std::vector<Card> &getCards(){ //get the pack function.
            return this->cards;
        }
    };

}
