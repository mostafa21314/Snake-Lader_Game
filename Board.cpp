#include "Board.h"
#include <iostream>
#include <iomanip>
#include <queue>
#include <algorithm>

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
                // If it's a normal tile, set destination to the next tile's position
                int nextTilePos;
                if(count==getSize()){
                    nextTilePos=count;
                }else{
                nextTilePos = count + 1;}
                subboard.emplace_back(count, -1, nextTilePos);
                addEdge(count,nextTilePos,1);
            } else {
                int randint;
                int futureVertex = -1;  // Initialize with an invalid value

                if (random_percentage > NORMAL_TILE_PERCENTAGE + ((100 - NORMAL_TILE_PERCENTAGE) * LaddertosnakeRatio)) {
                    std::uniform_int_distribution<int> distribution2(1, count);
                    randint = distribution2(gen);
                    futureVertex = randint;
                } else {
                    std::uniform_int_distribution<int> distribution2(count, rows_ * columns_);
                    randint = distribution2(gen);
                    futureVertex = randint;
                }

                if (count == rows_ * columns_) {
                    subboard.emplace_back(count, -1, -1);
                } else {
                    if (randint > count) {
                        tiletype = -2; // if ladder
                        subboard.emplace_back(count, tiletype, futureVertex);
                        const weightType EDGE_WEIGHT = abs(count - randint);
                        // Add edge to the graph
                        addEdge(count, randint, EDGE_WEIGHT); // Define EDGE_WEIGHT as needed
                    } else if (randint < count) {
                        tiletype = -3; // if snake
                        subboard.emplace_back(count, tiletype, futureVertex);
                        const weightType EDGE_WEIGHT = abs(count - randint);
                        // Add edge to the graph
                        addEdge(count, randint, EDGE_WEIGHT); // Define EDGE_WEIGHT as needed
                    } else {
                        subboard.emplace_back(count, -1, count+1);
                    }
                }
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
                // If it's a normal tile, set destination to the next tile's position
                int nextTilePos;
                if(count==getSize()){
                    nextTilePos=count;
                }else{
                    nextTilePos = count + 1;}
                subboard.emplace_back(count, -1, nextTilePos);
                addEdge(count,nextTilePos,1);
            } else {
                int randint;
                int futureVertex = -1;  // Initialize with an invalid value

                if (random_percentage > NORMAL_TILE_PERCENTAGE + ((100 - NORMAL_TILE_PERCENTAGE) * LaddertosnakeRatio)) {
                    std::uniform_int_distribution<int> distribution2(1, count);
                    randint = distribution2(gen);
                    futureVertex = randint;
                } else {
                    std::uniform_int_distribution<int> distribution2(count, min(count+(rows_*5),rows_ * columns_));
                    randint = distribution2(gen);
                    futureVertex = randint;
                }

                if (count == rows_ * columns_) {
                    subboard.emplace_back(count, -1, -1);
                } else {
                    if (randint > count) {
                        tiletype = -2; // if ladder
                        subboard.emplace_back(count, tiletype, futureVertex);
                        const weightType EDGE_WEIGHT = abs(count - randint);
                        // Add edge to the graph
                        addEdge(count, randint, EDGE_WEIGHT); // Define EDGE_WEIGHT as needed
                    } else if (randint < count) {
                        tiletype = -3; // if snake
                        subboard.emplace_back(count, tiletype, futureVertex);
                        const weightType EDGE_WEIGHT = abs(count - randint);
                        // Add edge to the graph
                        addEdge(count, randint, EDGE_WEIGHT); // Define EDGE_WEIGHT as needed
                    } else {
                        subboard.emplace_back(count, -1, count+1);
                    }
                }
            }
            count += 1; // Increment by 2 for each tile
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


// Map vertex number (0,1,2,..) to (A,B,C,..)
char Board::Vname(const int s) const
{
    return char(s+65);
}

// Get Graph from text File (file name is stored in string fname)
// Graph is stored in adjacency matrix, a copy is returned in A[][]


// Display Adjacency Matrix
void Board::dispGraph() const
{
    // Displaying the adjacency matrix

    // Displaying the connections between tiles based on the graph
    cout << "\nConnections between Tiles:\n";
    for (const auto& row : board_) {
        for (const Tile& tile : row) {
            cout << "Tile " << tile.pos << ": ";

            if (tile.type == -2) {
                cout << "Ladder to Tile " << tile.destination << endl;
            } else if (tile.type == -3) {
                cout << "Snake to Tile " << tile.destination << endl;
            } else {
                cout << "No connection" << endl;
            }
        }
    }
}

// Get Non-Zero edges from adjacency matrix
// and store them in array edges[].


// Get number of vertices (V)
int Board::No_of_Verices() const
{
    return V;
}

// Get Number of Non-zero edges (E)
int Board::No_of_Edges() const
{
    return E;
}

// Output an edge (e): Vertex names and weight
void Board::printEdge(Edge e) const
{
    cout << Vname(e.u) << " " << Vname(e.v) << " " << e.w << endl;
}

// Display Graph Edges
void Board::dispEdges() const
{
    std::cout << "Graph Edges:\n";
    for (const Edge& edge : edges) {
        std::cout << "Edge (" << edge.u << ", " << edge.v << ") with weight " << edge.w << "\n";
    }
}

// Shortest paths from node s
// uses Dijkstra's Algorithm
void Board::shPath(int s)
{
    // Implement the function here
}

// Print path (vertex names) from source (s) to destination (i)
void Board::printPath(int s, int i) const
{
    // Implement the function here
}

// Node Visit Function
void Board::visit(int k)
{
    // Implement the function here
}

// Depth First Search Traversal
void Board::DFS()
{
    // Implement the function here
}

// Minimum Spanning Tree
void Board::MST()
{
    // Implement the function here
}

void Board:: setNumNodes(int size){
    V = size;
}

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

            if (count >= 5) {
                int size = rows_ * columns_;
                std::uniform_int_distribution<int> distribution3(count, size);
                int destination = distribution3(gen);

                std::uniform_int_distribution<int> distribution4(1, 6);  // Adjust range as needed
                int randomnum = distribution4(gen);
                replaceTileByPosition(board_, tile.pos, -1, min(getSize(), tile.pos+1));// make the snake tile a normal tile to avoid a rare condition of still having 6 snakes when there is 12 initially
                updateEdgeByU(tile.pos,min(getSize(), tile.pos+1),1);
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

void Board::addEdge(int u, int v, int weight) {

        // Assuming an undirected graph
        edges.push_back({u, v, weight});
        map[u].push_back(v);

}

void Board::updateEdgeByU(int u, int newV, weightType newW) {
    for (Edge& edge : edges) {
        if (edge.u == u) {
            // Update the edge with new values for v and w
            edge.v = newV;
            edge.w = newW;
            // Assuming there's only one edge with the given u, you can break the loop
            break;
        }
    }
}

Edge Board::findEdgeByU(int u) {
    auto it = std::find_if(edges.begin(), edges.end(), [u](const Edge& edge) {
        return edge.u == u;
    });

    if (it != edges.end()) {
        return *it;
    } else {
        // If no matching edge is found, return an edge with default values
        return {0, 0, 0};  // You may need to adjust this depending on your Edge constructor
    }
}

void Board::printAdjacencyList() const {
    std::cout << "Adjacency List:\n";
    for (int i = 1; i < rows_*columns_; ++i) {
        std::cout << i << " -> ";
        for (int vertex : map[i]) {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
    }

}

void Board :: BFS (int startVertex, int V) { //note that V is the number of vertices
visited = new bool[V]; //visiting array
  for (int i = 0; i < V; i++)
    visited[i] = false; //all the vertices are unvisted
  list<int> queue;
  visited[startVertex] = true;
  queue.push_back(startVertex); //beginning at the start vertex
  list<int>::iterator i;
  while (!queue.empty()) {
    int currVertex = queue.front();
    cout << "Visited " << currVertex << " ";
    queue.pop_front();
    for (i = adjLists[currVertex].begin(); i != adjLists[currVertex].end(); ++i) {
      int adjVertex = *i;
      if (!visited[adjVertex]) { //if vertex is not visited
        visited[adjVertex] = true; //visit it
        queue.push_back(adjVertex);
      }
    }
  }
}



