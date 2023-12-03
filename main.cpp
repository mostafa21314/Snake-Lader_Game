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

    x.SetDifficulty(90);
    x.Setladdertosnakeratio(0.5);
    x.generateRandBoard();
    x.printBoard();
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

        currentPlayer.Play(x);

        // Check if the player won
        if (currentPlayer.Getpos() == x.getSize()) {
            std::cout << currentPlayer.getname() << " wins!" << std::endl;
            break;
        }

        // Add the player back to the end of the queue for the next turn
        playersQueue.push(currentPlayer);
    }

    return 0;





    return 0;
}
