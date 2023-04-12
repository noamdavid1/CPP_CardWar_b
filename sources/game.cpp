#include "game.hpp"
#include "card.hpp"
#include "player.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include <stdexcept>

namespace ariel
{
    

    Game::Game(Player &playera, Player &playerb) :player_a(playera), player_b(playerb)// initializtion of the constructor.
    {
        this->numofgame = 0;
        this->initialize_cards();
    }

    void Game::initialize_cards() //initializtion of the game
    {
        for (int rank = 2; rank <= 14; rank++) //the rank of the card, (14 is 'ACE').
        {
            for (char shape : {'C', 'H', 'S', 'D'}) //c-club, h-heart, s-spade, d-diamond.
            {
                this->getCards().push_back({rank, shape}); //make a pack of 52 cards.
            }
        }
        std::random_device rd; 
        std::mt19937 g(rd());
        std::shuffle(this->getCards().begin(), this->getCards().end(), g); //rendom suffling of the pack.

        //divide the pack into two players.
        int i = 0;
        while (i < 26)
        {
            Card temp = this->getCards().back();
            this->getCards().pop_back();
            this->player_a.get_player_cards().push(temp);
            i++;
        }
        int j = 0;
        while (j < 26)
        {
            Card temp = this->getCards().back();
            this->getCards().pop_back();
            player_b.get_player_cards().push(temp);
            j++;
        }
        this->winner = false; //no winner at the start of the game.
    }

    // play one turn.
    void Game::playTurn()
    {
        if (&this->player_a==&this->player_b) //checking if the players is not the same person.
        {
            throw std::exception();
        }
        if (this->player_a.stacksize() == 0 || this->player_b.stacksize() == 0) //checking if there are cards to play another turn.
        {
            this->winner = true; //if there are no cards left, game over and there is a winner.
            throw std::exception();
        }
        this->numofgame = numofgame + 1; //count number of games.
        //start a turn.
        Card carda = player_a.get_player_cards().top(); 
        player_a.get_player_cards().pop();
        Card cardb = player_b.get_player_cards().top();
        player_b.get_player_cards().pop();
        if (carda.getRank() > cardb.getRank())
        {
            //2 wins 'ACE'.
            if (carda.getRank() == 14 && cardb.getRank() == 2)
            {
                this->player_b.setCardst(2);
                this->player_b.setNumOfWin();
                turns.push(player_a.getName() + ":14, " + player_b.getName() + ":2, " + player_b.getName() + " has won this turn!");
            }
            else
            {
                turns.push(player_a.getName() + ":" + std::to_string(carda.getRank()) + "," + player_b.getName() + ":" + std::to_string(cardb.getRank()) + "," + player_a.getName() + " has won this turn!");
                this->player_a.setCardst(2);
                this->player_a.setNumOfWin();
            }
        }
        else if (carda.getRank() < cardb.getRank())
        {
            if (carda.getRank() == 2 && cardb.getRank() == 14)
            {
                turns.push(player_a.getName() + ":2, " + player_b.getName() + ":14, " + player_a.getName() + " has won this turn!");
                this->player_a.setCardst(2);
                this->player_a.setNumOfWin();
            }
            else
            {
                turns.push(player_a.getName() + ":" + std::to_string(carda.getRank()) + "," + player_b.getName() + ":" + std::to_string(cardb.getRank()) + "," + player_b.getName() + " has won this turn!");
                this->player_b.setCardst(2);
                this->player_b.setNumOfWin();
            }
        }
        //if there is a equal cards- start a war. 
        else
        {
            int remember = 0;
            while (player_a.stacksize() > 0 && player_b.stacksize() > 0)
            {
                //taking out face-down cards.
                carda = player_a.get_player_cards().top();
                player_a.get_player_cards().pop();
                cardb = player_b.get_player_cards().top();
                player_b.get_player_cards().pop();
                //checking if there is more cards to take out for the war.
                if (player_a.stacksize() == 0 && player_b.stacksize() == 0) //if there are no cards left- distribution of the cards equally to both players. 
                {
                    this->player_a.setCardst((4 + remember) / 2);
                    this->player_b.setCardst((4 + remember) / 2);
                    this->winner = true;
                    break;
                }
                //the war cards.
                Card carda1 = player_a.get_player_cards().top();
                Card cardb1 = player_b.get_player_cards().top();
                if (carda1.getRank() > cardb1.getRank())
                {
                    player_a.get_player_cards().pop();
                    player_b.get_player_cards().pop();
                    if (carda1.getRank() == 14 && cardb1.getRank() == 2)
                    {
                        turns.push(player_a.getName() + ":14, " + player_b.getName() + ":2, " + player_b.getName() + " has won this turn!");
                        this->player_b.setCardst(6 + remember);
                        this->player_b.setNumOfWin();
                        break;
                    }
                    else
                    {
                        turns.push(player_a.getName() + ":" + std::to_string(carda.getRank()) + "," + player_b.getName() + ":" + std::to_string(cardb.getRank()) + "," + player_a.getName() + " has won this turn!");
                        this->player_a.setCardst(6 + remember);
                        this->player_a.setNumOfWin();
                        break;
                    }
                }
                else if (carda1.getRank() < cardb1.getRank())
                {
                    player_a.get_player_cards().pop();
                    player_b.get_player_cards().pop();
                    if (carda1.getRank() == 2 && cardb1.getRank() == 14)
                    {
                        turns.push(player_a.getName() + ":2, " + player_b.getName() + ":14, " + player_a.getName() + " has won this turn!");
                        this->player_a.setCardst(6 + remember);
                        this->player_a.setNumOfWin();
                        break;
                    }
                    else
                    {
                        turns.push(player_a.getName() + ":" + std::to_string(carda.getRank()) + "," + player_b.getName() + ":" + std::to_string(cardb.getRank()) + "," + player_b.getName() + " has won this turn!");
                        this->player_b.setCardst(6 + remember);
                        this->player_b.setNumOfWin();
                        break;
                    }
                }
                //if the cards equal again 'remember' rememers the cards that already pop out of the stack.
                else if (carda1.getRank() == cardb1.getRank())
                {
                    remember = remember + 2;
                }
            }
            //if there is no cards left, game over and there is a winner.
            if (player_a.stacksize() == 0 && player_b.stacksize() == 0)
            {
                this->winner = true;
            }
        }
    }
    // print the last turn stats.
    void Game::printLastTurn()
    {
        std::cout << turns.top() << std::endl;
    }
    // playes the game untill the end.
    void Game::playAll()
    {
        while (player_a.stacksize() > 0 && player_b.stacksize() > 0)
        {
            playTurn();
        }
        this->winner = true; //plays all the turns-game over and there is a winner.
    }
    // prints the name of the winning player
    void Game::printWiner() //prints the winner by checking the numbers of cards taken.
    {
        if (player_a.cardesTaken() > player_b.cardesTaken())
        {
            std::cout << "the winner is:" << this->player_a.getName() << std::endl;
        }
        else if (player_a.cardesTaken() < player_b.cardesTaken())
        {
            std::cout << "the winner is:" << player_b.getName() << std::endl;
        }
        else
        {
            std::cout << "the game over with a tie!" << std::endl;
            // throw std::exception();
        }
    }
    // prints all the turns played one line per turn.
    void Game::printLog()
    {
        while (!turns.empty())
        {
            std::string temp = turns.top();
            turns.pop();
            std::cout << temp << std::endl;
        }
    }
    // for each player prints basic statistics.
    void Game::printStats()
    {
        this->player_a.setStatus(this->numofgame);
        this->player_b.setStatus(this->numofgame);
        this->player_a.getStatus();
        this->player_b.getStatus();
    }
}
