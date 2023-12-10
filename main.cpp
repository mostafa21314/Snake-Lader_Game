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
    Board x; // board initialization

    // number of rows and columns for manual insertion
    int row = 10;
    int column = 10;
    int userpos = 1;
    int input;
    int numofmoves;


    //calling class functions to customize the board
    x.SetDifficulty(20); // whenever the difficulty is set below 40 the bfs has issues maybe because unsolvable?
    x.Setladdertosnakeratio(0.5);
    x.generateBoard(10,10);
    x.dispEdges();
    numofmoves = x.BFS();


// Queue system for the players
    int numPlayers;
    std::cout << "Enter the number of players: ";
    std::cin >> numPlayers;

    std::queue<Players> playersQueue; // create queue of players

    // Create and enqueue players based on user input
    for (int i = 1; i <= numPlayers; ++i) {
        playersQueue.push(Players("Player " + std::to_string(i)));
    }

    while (!playersQueue.empty()) {
        Players currentPlayer = playersQueue.front();
        playersQueue.pop();

        std::cout << "It's " << currentPlayer.getname() << "'s turn." << std::endl;

        int xz = currentPlayer.Play(x);
        int sixcounter = 0; // for rolling 3 6s in a row

        while(xz == 6 && sixcounter < 2){  // the roll number is returned if it is a 6 the counter increases by 1
            sixcounter++;
            cout << "It's " << currentPlayer.getname() << "'s turn." << std::endl;
            xz = currentPlayer.Play(x);

            // Check if the player won


        }

        if (xz == 66) { // 66 is returned if the player wins by reaching last tile or takes a ladder connecting to last tile
            std::cout << currentPlayer.getname() << " wins!" << std::endl;
            if(currentPlayer.getnumofmoves()==numofmoves){ // if the player gets the best path they get this message (BFS)
                cout << "You GOT THE LUCKIEST PATH" << endl;
            }
            break;
        }

        // Add the player back to the end of the queue for the next turn
        playersQueue.push(currentPlayer);
    }

    return 0;




}
