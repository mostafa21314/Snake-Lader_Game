#include "Board.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <random>
#include <ctime>



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
                    addEdge(count,count,0);
                } else {
                    if (randint > count) {
                        tiletype = -2; // if ladder
                        const weightType EDGE_WEIGHT = abs(count - randint);
                        // Add edge to the graph
                        addEdge(count, randint, EDGE_WEIGHT); // Define EDGE_WEIGHT as needed
                    } else if (randint < count) {
                        tiletype = -3; // if snake
                        const weightType EDGE_WEIGHT = abs(count - randint);
                        // Add edge to the graph
                        addEdge(count, randint, EDGE_WEIGHT); // Define EDGE_WEIGHT as needed
                    } else {
                        addEdge(count,count+1,1);
                    }
                }
            }
            count += 1; // Increment by 2 for each tile
        }

    }
    Boardfixer();
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
                    addEdge(count,count,0);
                } else {
                    if (randint > count) {
                        tiletype = -2; // if ladder
                        const weightType EDGE_WEIGHT = abs(count - randint);
                        // Add edge to the graph
                        addEdge(count, randint, EDGE_WEIGHT); // Define EDGE_WEIGHT as needed
                    } else if (randint < count) {
                        tiletype = -3; // if snake
                        const weightType EDGE_WEIGHT = abs(count - randint);
                        // Add edge to the graph
                        addEdge(count, randint, EDGE_WEIGHT); // Define EDGE_WEIGHT as needed
                    } else {
                        addEdge(count,count+1,1);
                    }
                }
            }
            count += 1; // Increment by 2 for each tile
        }

    }
    Boardfixer();
    return rows_*columns_;
}

void Board::SetDifficulty(int x) {
    NORMAL_TILE_PERCENTAGE = x;
}








int Board::getSize() {
    return rows_*columns_;
}

void Board::Setladdertosnakeratio(float x) {
    LaddertosnakeRatio = x;

}


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
    cout << e.u << " " << e.v << " " << e.w << endl;
}

// Display Graph Edges
void Board::dispEdges() const
{
    std::cout << "Graph Edges:\n";
    for (const Edge& edge : edges) {
        std::cout << "Edge (" << edge.u << ", " << edge.v << ") with weight " << edge.w << "\n";
    }
}

void Board::Boardfixer() {
    std::random_device rd;
    std::mt19937 gen(rd());

    int count = 0;

    for (int i = 0; i < getSize(); i++) {

            if (edges[i].u>edges[i].v) {
                count++;
            } else if (edges[i].u<edges[i].v) {  // Fix the condition here
                count = 0;
            }

            if (count >= 5) {
                int size = rows_ * columns_;
                std::uniform_int_distribution<int> distribution3(count, size);
                int destination = distribution3(gen);

                std::uniform_int_distribution<int> distribution4(1, 6);  // Adjust range as needed
                int randomnum = distribution4(gen);
                updateEdgeByU(edges[i].u,min(getSize(), edges[i].u+1),1); // make the snake tile a normal tile to avoid a rare condition of still having 6 snakes when there is 12 initially
            }

    }
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

void Board :: BFS (int start, list<int> map[Vmax]) { //algorithm for the Breadth-First Search
  visited = new bool[V]; //list of visited arrays
  for (int i = 0; i < V; i++)
    visited[i] = false; //mark all as unvisted

  list<int> queue; //queue of all nodes

  visited[start] = true; //mark the source node as already visited
  queue.push_back(start); //make start the first node in queue

  list<int>::iterator i; //iterator to traverse the queue

  while (!queue.empty()) { //while there are still nodes to explore
    int currVertex = queue.front(); //get the front
    cout << "Visited " << currVertex << " "; //front now visited (WE WON'T NEED IT LATER)
    queue.pop_front(); //remove from queue

    for (i = map[currVertex].begin(); i != map[currVertex].end(); ++i) {
      int adjVertex = *i; //get index of adjacent vertex
      if (!visited[adjVertex]) { //if it hasn't been visited
        visited[adjVertex] = true; //visit it
        queue.push_back(adjVertex); //put it in the queue
      }
    }
  }
}

Board::~Board() {

}



