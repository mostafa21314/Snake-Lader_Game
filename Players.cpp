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
    int rollnum;

    cout << "Do you want to roll the dice? press 1 " << endl;
    cin >> input;
    if (input == 1) {
        bool torf = Rolldice(x,rollnum);


        if(torf){
        if (x.findEdgeByU(position).w == 1) {
            if(rollnum == 0){
                cout << "You have rolled 6 three times in a row which renders ur turn void" << endl;
            } else {
            cout << "You have moved to tile " << position << endl;}
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
            return 66;
        }

        return rollnum;

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

bool Players::Rolldice(Board x,int& result) {
    Dice v;
    int input;
    int result1;
    result = v.roll();
    result1 = result;
    if(result == 6){
        sixcounter++;
    } else{
        sixcounter = 0;
    }

    if(sixcounter!=3) {

        if (position + result <= x.getSize()) {
            position = position + result;
        } else {
            cout << "You rolled a " << result << " which is " << result - (x.getSize() - position)
                 << " more than required, Try again!" << endl;
            return false;
        }


    } else {
        result = 0;
    }
    cout << "You rolled: " << result1 << endl;
    return true;
}
