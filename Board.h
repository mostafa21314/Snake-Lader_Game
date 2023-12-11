#ifndef BOARD_H
#define BOARD_H

using namespace std;
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream>
#include <string>
#include <vector>
#include "Edge.h"
#include <list>


const int Vmax = 250;					// Maximum number of vertices
const int Emax = Vmax*(Vmax-1)/2;
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
    int  No_of_Verices() const;			// Get number of vertices (V)
    int  No_of_Edges() const;			// Get Number of Non-zero edges (E)
    void dispEdges() const;				// Display Graph edges
    void generateBoard(int rows, int columns);
    int generateRandBoard();
    int getSize();
    void SetDifficulty(int x);
    void Setladdertosnakeratio(float x);
    void addEdge(int u, int v, weightType weight);
    void updateEdgeByU(int u, int newV, weightType newW);
    Edge findEdgeByU(int u);
    void printAdjacencyList() const;
    int BFS();
    void BFS (int start, list<int> map[Vmax]);


    void Boardfixer();


private:
    // Private member variables


    int V, E;							// No.of vertices (V) and edges (E)
    vector<Edge> edges;			// Array of non-zero edges
    list<int> map[Vmax];
    Edge tree[Vmax];						// MST
    weightType distance[Vmax];			// Distance array for shortest paths
    int via[Vmax];						// Via array for shortest paths
    bool processed[Vmax];				// processed array for shortest paths
    int order;							// Order of Visit of a node in the DFS
    int val[Vmax];
    std::vector<bool> visited;     // Array holding order of traversal of nodes
    vector<int> path;

    void printEdge(Edge e) const;		// Output an edge (e)

    int rows_;
    int columns_;
    int NORMAL_TILE_PERCENTAGE = 85;
    float LaddertosnakeRatio;

};

#endif  // BOARD_H
