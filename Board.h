#ifndef BOARD_H
#define BOARD_H

using namespace std;
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream>

struct Tile {
    int pos;
    int destination;
    int type;

    Tile(int x, int y, int z) : pos(x), type(y), destination(z) {}
};

class Board {
public:
    // Constructor
    Board();


    // Destructor (if needed)
    ~Board();

    // Public member functions
    void generateBoard(int rows, int columns);
    void printBoard() const;
    int generateRandBoard();
    int getSize();
    void SetDifficulty(int x);
    Tile findTileByPos(int pos) const;
    // Getter for the board
    const std::vector<std::vector<Tile>>& getBoard() const;


private:
    // Private member variables
    int rows_;
    int columns_;
    vector<vector<Tile>> board_;
    int NORMAL_TILE_PERCENTAGE = 85;

};

#endif  // BOARD_H
