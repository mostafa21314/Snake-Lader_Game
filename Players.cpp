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

//constructor position always starts at 1
Players::Players(string name) {
    Name = name;
    position = 1;

}

// Play function plays for one turn by rolling a dice and moving positions and checking if there is a snake or ladder to move accordingly
int Players::Play(Board x) {
    int input;
    int rollnum;

    cout << "Do you want to roll the dice? press 1 " << endl;
    cin >> input;
    if (input == 1) {
        bool torf = Rolldice(x,rollnum); // this is to make sure that the player does not have an illegal turn


        if(torf){ // illegal turn checker
        if (x.findEdgeByU(position).w == 1) { // if normal tile
            if(rollnum == -1){ // rollnum is passed by reference if it is zero then a rule has been violated
                cout << "You have rolled 6 three times in a row which renders ur turn void" << endl;
            } else {
            cout << "You have moved to tile " << position << endl;} //normal tile movement
        } else if (x.findEdgeByU(position).u<x.findEdgeByU(position).v) { //if destiination bigger than position meaning ladder
            int old = position;
            position = x.findEdgeByU(position).v;
            cout << "Your tile was a ladder. You moved from tile " << old << " to tile " << position << endl;
            if(x.findEdgeByU(position).w == 0){ //if weight is 0 means on the winning tile from a ladder so the winning code is returned
                return 66;
            }
        } else if (x.findEdgeByU(position).u>x.findEdgeByU(position).v) { // if destination less than position so snake
            int old = position;
            position = x.findEdgeByU(position).v;
            cout << "Your tile was a snake. You moved from tile " << old << " to tile " << position << endl;
        } else if(x.findEdgeByU(position).w == 0){ // if weight is 0 means on the winning tile from a normal move so the winning code is returned
            return 66;
        }



        return rollnum;

        }}


    return position;

}

//changes position
void Players::updatepos(int x) {
    position = x;

}
//returns a name
string Players::getname() {
    return Name;
}
// returns position
int Players::Getpos() {
    return position;
}
// simple roll dice function that makes sure no illegal move is made
bool Players::Rolldice(Board x,int& result) {
    Dice v;
    int input;
    int result1;
    result = v.roll();
    numofmoves++;
    result1 = result;
    if(result == 6){ // if six is rolled counter increases to check for three sixes in a row
        sixcounter++;
    } else{
        sixcounter = 0; // resets counter
    }

    if(sixcounter!=3) { //if the rule has not been broken proceed normally

        if (position + result <= x.getSize()) {
            position = position + result;
        } else {  // overshooting the winning tile
            cout << "You rolled a " << result << " which is " << result - (x.getSize() - position)
                 << " more than required, Try again!" << endl;
            return false;
        }


    } else {
        result = -1; // rule violated so -1 returned for error message
    }
    cout << "You rolled: " << result1 << endl; // for visual only
    return true;
}

int Players::getnumofmoves() {
    return numofmoves;
}
