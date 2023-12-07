#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <queue>
#include "Board.h"
#include "Dice.h"
#include "Players.h"

int main() {
    Board x;
    int row = 4;
    int column = 4;
    int userpos = 1;
    int input;

    x.SetDifficulty(50);
    x.Setladdertosnakeratio(0.5);
    x.generateBoard(10,10);
    x.dispEdges();

    int numPlayers;
    std::cout << "Enter the number of players: ";
    std::cin >> numPlayers;

    std::queue<Players> playersQueue;

    // Create and enqueue players based on user input
    for (int i = 1; i <= numPlayers; ++i) {
        playersQueue.push(Players("Player " + std::to_string(i)));
    }

    while (!playersQueue.empty()) {
        Players currentPlayer = playersQueue.front();
        playersQueue.pop();

        std::cout << "It's " << currentPlayer.getname() << "'s turn." << std::endl;

        int xz = currentPlayer.Play(x);
        int sixcounter = 0;

        while(xz == 6 && sixcounter < 2){
            sixcounter++;
            cout << "It's " << currentPlayer.getname() << "'s turn." << std::endl;
            xz = currentPlayer.Play(x);

            // Check if the player won
            if (currentPlayer.Getpos() == x.getSize() || xz == 66) {
                std::cout << currentPlayer.getname() << " wins!" << std::endl;
                break;
            }

        }

        // Add the player back to the end of the queue for the next turn
        playersQueue.push(currentPlayer);
    }

    return 0;




}
