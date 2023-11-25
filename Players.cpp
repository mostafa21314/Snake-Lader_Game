//
// Created by Marwan on 11/25/2023.
//

#include "Players.h"

Players::Players(string name) {
    Name = name;
    position = 1;

}

int Players::Play(int max) {
    Dice x;
    int result = x.roll();
    if(position + result <= max){
        position = position + result;
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
