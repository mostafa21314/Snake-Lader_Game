#include "Board.h"
#include <iostream>

Board::Board() {
}

void Board::generateBoard(int rows, int columns) {
    rows_ = rows;
    columns_ = columns;
    int count = 1;

    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Use the member variables rows_ and columns_ instead of generating new random values
    for (int i = 0; i < rows_; i++) {
        std::vector<Tile> subboard;

        for (int j = 0; j < columns_; j++) {
            int tiletype = -1;
            std::uniform_int_distribution<int> distribution(0, 99);
            int random_percentage = distribution(gen);

            if (random_percentage < NORMAL_TILE_PERCENTAGE) {
                subboard.emplace_back(count, -1, tiletype);
            } else {
                int randint;
                if(random_percentage > NORMAL_TILE_PERCENTAGE + ((100 - NORMAL_TILE_PERCENTAGE)*LaddertosnakeRatio)){
                    std::uniform_int_distribution<int> distribution2(1, count);
                    randint = distribution2(gen);
                } else{
                    std::uniform_int_distribution<int> distribution2(count, rows_ * columns_);
                    randint = distribution2(gen);
                }

                if (count  == rows_*columns_) {
                    subboard.emplace_back(count, -1, -1);


                } else {


                if (randint > count) {
                    tiletype = -2; // if ladder
                    subboard.emplace_back(count, tiletype, randint);
                } else if (randint < count) {
                    tiletype = -3; // if snake
                    subboard.emplace_back(count, tiletype, randint);
                } else {
                    subboard.emplace_back(count, -1, -1);
                }}


            }
            count += 1; // Increment by 2 for each tile
        }
        board_.push_back(subboard);
    }
    Boardfixer();
}

void Board::printBoard() const {
    for (const auto& row : board_) {
        for (const auto& tile : row) {
            std::cout << "{" << tile.pos << "," << tile.type << "," << tile.destination << "} ";
        }
        std::cout << std::endl;
    }
}

int Board::generateRandBoard() {
    srand(std::time(0));
    int randinteger = std::rand() % 11 + 5;
    rows_ = randinteger;
    columns_ = randinteger;
    int count = 1;

    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Use the member variables rows_ and columns_ instead of generating new random values
    for (int i = 0; i < rows_; i++) {
        std::vector<Tile> subboard;

        for (int j = 0; j < columns_; j++) {
            int tiletype = -1;



            std::uniform_int_distribution<int> distribution(0, 99);
            int random_percentage = distribution(gen);

            if (random_percentage < NORMAL_TILE_PERCENTAGE) {
                subboard.emplace_back(count, -1, tiletype);
            } else {
                int randint;
                if(random_percentage > NORMAL_TILE_PERCENTAGE + ((100 - NORMAL_TILE_PERCENTAGE)*LaddertosnakeRatio)){
                    std::uniform_int_distribution<int> distribution2(1, count);
                    randint = distribution2(gen);
                } else{
                    std::uniform_int_distribution<int> distribution2(count, rows_ * columns_);
                    randint = distribution2(gen);
                }
                if (randint > count) {
                    tiletype = -2; // if ladder
                    subboard.emplace_back(count, tiletype, randint);
                } else if (randint < count) {
                    tiletype = -3; // if snake
                    subboard.emplace_back(count, tiletype, randint);
                }else if (count  == rows_*columns_) {
                    subboard.emplace_back(count, -1, -1);
                } else {
                        subboard.emplace_back(count, -1, -1);
                    }
            }
            count += 1; // Increment by 1 for each tile
        }
        board_.push_back(subboard);
    }
    Boardfixer();
    return rows_*columns_;
}

void Board::SetDifficulty(int x) {
    NORMAL_TILE_PERCENTAGE = x;
}

Board::~Board() {
}

const std::vector<std::vector<Tile>> &Board::getBoard() const {
    return board_;
}

Tile Board::findTileByPos(int pos) const {
    for (const auto& row : board_) {
        for (const auto& tile : row) {
            if (tile.pos == pos) {
                return tile;
            }
        }
    }
    // Return a default Tile with all values set to -1 if not found
    return Tile(pos, -1, -1);
}

int Board::getSize() {
    return rows_*columns_;
}

void Board::Setladdertosnakeratio(float x) {
    LaddertosnakeRatio = x;

}

#include <iostream>
#include <random>
#include <ctime>

void Board::Boardfixer() {
    std::random_device rd;
    std::mt19937 gen(rd());

    int count = 0;

    for (auto& row : board_) {
        for (auto& tile : row) {
            if (tile.type == -3) {
                count++;
            } else if (tile.type == -2) {  // Fix the condition here
                count = 0;
            }

            if (count >= 6) {
                int size = rows_ * columns_;
                std::uniform_int_distribution<int> distribution3(count, size);
                int destination = distribution3(gen);

                std::uniform_int_distribution<int> distribution4(1, 6);  // Adjust range as needed
                int randomnum = distribution4(gen);

                int newpos = tile.pos - randomnum;
                replaceTileByPosition(board_, newpos, -2, destination);
            }
        }
    }
}


void Board::replaceTileByPosition(vector <std::vector<Tile>> &board, int x, int newValue, int newdestination) {
    for (auto& row : board) {
        for (auto& tile : row) {
            if (tile.pos == x) {
                tile.type = newValue;
                tile.destination = newdestination;
                return; // Break out of the loop once the tile is replaced
            }
        }
    }

    // If control reaches here, the position was not found
    std::cout << "Tile with position " << x << " not found." << std::endl;

}

