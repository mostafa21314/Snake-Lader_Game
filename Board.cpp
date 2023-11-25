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
                std::uniform_int_distribution<int> distribution2(1, rows_ * columns_);
                int randint = distribution2(gen);

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
    rows_ = std::rand() % 16 + 5;
    columns_ = std::rand() % 16 + 5;
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
                std::uniform_int_distribution<int> distribution2(1, rows_ * columns_);
                int randint = distribution2(gen);

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
