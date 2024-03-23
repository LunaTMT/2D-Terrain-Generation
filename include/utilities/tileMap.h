#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <random>
#include "PerlinNoise.hpp"
#include "globals.h"

class TileMap {
private:
    int rows;
    int cols;
    int** map;

public:
    // Constructor
    TileMap(int numRows, int numCols);

    // Destructor
    ~TileMap();

    // Setter for setting a tile value at a specific row and column
    void setTile(int row, int col, int value);

    // Getter for retrieving the value of a tile at a specific row and column
    int getTile(int row, int col) const;

    // Generate tile map function
    void generateTileMap();



    // Operator overloading for accessing map as 2D array
    int* operator[](int row) const;
};

#endif // TILEMAP_H
