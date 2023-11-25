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

public:
    Players(string name);

    int Play(int max);

    void updatepos(int x);

    int Getpos();

    string getname();




};


#endif //SNAKE_AND_LADDER_PLAYERS_H
