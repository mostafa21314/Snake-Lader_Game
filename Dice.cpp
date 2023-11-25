#include "Dice.h"

#include <cstdlib>
#include <ctime>




Dice::Dice(){
    std::srand(std::time(0));

}

int Dice::roll() const {
    // Generate a random number between 1 and 6 for a six-sided die
    return std::rand() % 6 + 1;
}
