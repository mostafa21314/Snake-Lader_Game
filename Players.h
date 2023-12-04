//
// Created by Marwan on 11/25/2023.
//
#include <string>
#include "Dice.h"
#include "Board.h"
using namespace std;

#ifndef SNAKE_AND_LADDER_PLAYERS_H
#define SNAKE_AND_LADDER_PLAYERS_H


class Players {
private:
    int  position;
    string Name;
    int sixcounter = 0;

public:
    Players(string name);

    int Play(Board x);

    bool Rolldice(Board x, int&result);

    void updatepos(int x);

    int Getpos();

    string getname();




};


#endif //SNAKE_AND_LADDER_PLAYERS_H
