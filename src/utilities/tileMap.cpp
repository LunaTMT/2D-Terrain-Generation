#include "tileMap.h"

// Constructor
TileMap::TileMap(int numRows, int numCols) : rows(numRows), cols(numCols) {
    // Allocate memory for the tile map
    map = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        map[i] = new int[cols];
    }

    generateTileMap();
}

// Destructor
TileMap::~TileMap() {
    // Deallocate memory for the tile map
    for (int i = 0; i < rows; ++i) {
        delete[] map[i];
    }
    delete[] map;
}

// Setter for setting a tile value at a specific row and column
void TileMap::setTile(int row, int col, int value) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        map[row][col] = value;
    } else {
        // Handle invalid row or column
        // You can throw an exception, print an error message, or handle it in any other way you prefer
    }
}

// Getter for retrieving the value of a tile at a specific row and column
int TileMap::getTile(int row, int col) const {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        return map[row][col];
    } else {
        // Handle invalid row or column
        // You can throw an exception, print an error message, or handle it in any other way you prefer
        return -1; // Return a default value indicating an error
    }
}

// Generate tile map function
void TileMap::generateTileMap() {
    // Create multiple Perlin noise layers with different frequencies and amplitudes
    std::vector<float> frequencies = {0.00001f, 0.001f, 0.1f}; // Adjust frequencies for more or fewer hills
    std::vector<float> amplitudes = {60.f, 50.f, 25.f}; // Adjust amplitudes for higher or lower hills

    // SEED PERLIN
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(1, 1000000);
    const siv::PerlinNoise::seed_type seed = dist(rng);
    const siv::PerlinNoise perlin(seed);

    // Generate terrain
    for (int j = 0; j < cols; ++j) {
        //Gets the noise value for col height
        float height = 0.f;
        for (size_t k = 0; k < frequencies.size(); ++k) {
            float perlinValue = perlin.noise1D_01(static_cast<float>(j) * frequencies[k]) * amplitudes[k];
            height += perlinValue;
        }
        int grass_height = static_cast<int>(std::round(height));

        for (int i = 0; i < rows; ++i) {
            int diff = std::abs(grass_height - i);
            
            if (i < grass_height) {
                map[i][j] = SKY;
            } else if (diff <= 0) {
                map[i][j] = GRASS;
            } else if (diff <= 10) {
                map[i][j] = DIRT;
            } else {
                map[i][j] = STONE;
            }
        }
    }
}

// Operator overloading for accessing map as 2D array
int* TileMap::operator[](int row) const {
    return map[row];
}

