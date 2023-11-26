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
    user1.Play(x);





    return 0;
}
