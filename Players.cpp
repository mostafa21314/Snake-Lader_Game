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
    while (input == 1) {
        Rolldice(x);


        if (x.findTileByPos(position).type == -1) {
            cout << "You have moved to tile " << x.findTileByPos(position).pos << endl;
        } else if (x.findTileByPos(position).type == -2) {
            int old = position;
            position = x.findTileByPos(position).destination;
            cout << "Your tile was a ladder. You moved from tile " << old << " to tile " << position << endl;
        } else if (x.findTileByPos(position).type == -3) {
            int old = position;
            position = x.findTileByPos(position).destination;
            cout << "Your tile was a snake. You moved from tile " << old << " to tile " << position << endl;
        }

        cout << "Do you want to roll the dice? Press 1." << endl;
        cin >> input;

        if (position == x.getSize()){
            cout << "You Win!";
            break;
        }}


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
    }

}
