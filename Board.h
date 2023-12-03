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


const int Vmax = 200;					// Maximum number of vertices
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
    char Vname(const int s) const;		// Map vertex number to a name (character)
    void getGraph(string fname);		// Get Graph from text File (fname)
    void dispGraph() const;				// Display Ajacency Matrix
    int  No_of_Verices() const;			// Get number of vertices (V)
    int  No_of_Edges() const;			// Get Number of Non-zero edges (E)
    void dispEdges() const;				// Display Graph edges
    void MST();							// Minimum Spanning Tree (MST)
    void shPath(int s);					// Shortest paths from node (s)
    void DFS();							// Depth First Search Traversal (DFS)
    void AdjacencyList(string fname, int);
    void setNumNodes(int);
    void generateBoard(int rows, int columns);
    void printBoard() const;
    int generateRandBoard();
    int getSize();
    void SetDifficulty(int x);
    void Setladdertosnakeratio(float x);
    Tile findTileByPos(int pos) const;
    void addEdge(int u, int v, weightType weight);
    const std::vector<std::vector<Tile>>& getBoard() const;
    void replaceTileByPosition(std::vector<std::vector<Tile>>& board, int x, int newValue, int newdestination);
    void fileAppend(string);
    void updateEdgeByU(int u, int newV, weightType newW);
    Edge findEdgeByU(int u);


    void Boardfixer();


private:
    // Private member variables


    int V, E;							// No.of vertices (V) and edges (E)
    vector<Edge> edges;			// Array of non-zero edges
    Edge tree[Vmax];						// MST
    weightType distance[Vmax];			// Distance array for shortest paths
    int via[Vmax];						// Via array for shortest paths
    bool processed[Vmax];				// processed array for shortest paths
    int order;							// Order of Visit of a node in the DFS
    int val[Vmax];						// Array holding order of traversal of nodes

    void getEdges();						// Get Non-Zero edges from adjacency matrix
    void printEdge(Edge e) const;		// Output an edge (e)
    void printPath(int s,int i) const;	// Print path from source (s) to destination (i)
    void visit(int k);

    int rows_;
    int columns_;
    vector<vector<Tile>> board_;
    int NORMAL_TILE_PERCENTAGE = 85;
    float LaddertosnakeRatio;

};

#endif  // BOARD_H
