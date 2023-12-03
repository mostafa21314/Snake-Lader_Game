//
// Created by Marwan on 11/25/2023.
//
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include "Board.h"
#include "Dice.h"
#include "Players.h"

Players::Players(string name) {
    Name = name;
    position = 1;

}

int Players::Play(Board x) {
    int input;

    cout << "Do you want to roll the dice? press 1 " << endl;
    cin >> input;
    if (input == 1) {
        Rolldice(x);


        if (x.findEdgeByU(position).w == 1) {
            cout << "You have moved to tile " << position+1 << endl;
        } else if (x.findEdgeByU(position).u<x.findEdgeByU(position).v) {
            int old = position;
            position = x.findEdgeByU(position).v;
            cout << "Your tile was a ladder. You moved from tile " << old << " to tile " << position << endl;
        } else if (x.findEdgeByU(position).u>x.findEdgeByU(position).v) {
            int old = position;
            position = x.findEdgeByU(position).v;
            cout << "Your tile was a snake. You moved from tile " << old << " to tile " << position << endl;
        }

        if (position == x.getSize()){
            cout << "You Win!";
        }

        }


    return position;

}

void Players::updatepos(int x) {
    position = x;

}

string Players::getname() {
    return Name;
}

int Players::Getpos() {
    return position;
}

void Players::Rolldice(Board x) {
    Dice v;
    int input;
    int result = v.roll();
    if(position + result <= x.getSize()){
        position = position + result;
    } else {
        cout << "You rolled a " << result << " which is " << result - (x.getSize() - position) << "  than required, Try again!" << endl;
    }

}
