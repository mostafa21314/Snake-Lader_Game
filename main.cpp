#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
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
    int total = x.generateRandBoard();
    x.printBoard();


    Players user1("Marwan");



    cout << "Do you want to roll the dice? press 1 " << endl;
    cin >> input;
    while (input == 1){

            userpos = user1.Play(total); // Update userpos directly
             if (x.findTileByPos(userpos).type == -1) {
                cout << "You have moved to tile " << x.findTileByPos(userpos).pos << endl;
            } else if (x.findTileByPos(userpos).type == -2) {
                int old = userpos;
                userpos = x.findTileByPos(userpos).destination;
                user1.updatepos(userpos);
                cout << "Your tile was a ladder. You moved from tile " << old << " to tile " << userpos << endl;
            } else if (x.findTileByPos(userpos).type == -3) {
                int old = userpos;
                userpos = x.findTileByPos(userpos).destination;
                user1.updatepos(userpos);
                cout << "Your tile was a snake. You moved from tile " << old << " to tile " << userpos << endl;
            }
            if (userpos == total){
                cout << "You Win!";
                break;
            }

        cout << "Do you want to roll the dice? Press 1." << endl;
            cin >> input;

    }




    return 0;
}
