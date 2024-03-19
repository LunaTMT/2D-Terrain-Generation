#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <random>
#include <unordered_map>
#include "PerlinNoise.hpp" // Include the Perlin noise header

// Constants
const float SCREEN_WIDTH = 800.f;
const float SCREEN_HEIGHT = 600.f;

// Player view
const int COLS = 32;
const int ROWS = 24;

const float TILE_SIZE = SCREEN_WIDTH / COLS;
const float BORDER_THICKNESS = 1.f;

// Tile map dimensions
const int mapRows = 1200;
const int mapCols = 4200;

const float mapTileWidth = SCREEN_WIDTH / mapCols;
const float mapTileHeight = SCREEN_HEIGHT / mapRows;

// Colours
const sf::Color SKY_COLOR(135, 206, 250);    // Sky Blue
const sf::Color GRASS_COLOR(34, 139, 34);    // Dark Green
const sf::Color DIRT_COLOR(139, 69, 19);     // Brown
const sf::Color STONE_COLOR(169, 169, 169);  // Dark Gray


/*

    Small: Width = 4200 blocks, Height = 1200 blocks.
Medium: Width = 6300 blocks, Height = 1800 blocks.
Large: Width = 8400 blocks, Height = 2400 blocks.
*/


// Terrain enum
enum Terrain {
    SKY,
    GRASS,
    DIRT,
    STONE
};

// function prototypes
void generate_terrain(int ** tileMap);


// Function definitions
void dealocateTileMap(int** tileMap) {
    for (int i = 0; i < mapRows; ++i) {
        delete[] tileMap[i];
    }
    delete[] tileMap;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flat 2D World Generation");
    window.setFramerateLimit(60);

    sf::CircleShape dot(2.f);
    dot.setFillColor(sf::Color::Red);

    int** tileMap = new int*[mapRows];
    for (int i = 0; i < mapRows; ++i) {
        tileMap[i] = new int[mapCols];
    }

    generate_terrain(tileMap);

    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) 
                generate_terrain(tileMap);
            }

        window.clear(); // Clear the window each frame
        
        // Render the terrain
        for (int i = 0; i < mapRows; ++i) {
            for (int j = 0; j < mapCols; ++j) {
                float posX = j * mapTileWidth;
                float posY = i * mapTileHeight;

                // Ensure posX and posY are within the screen bounds
                if (posX >= SCREEN_WIDTH || posY >= SCREEN_HEIGHT) {
                    continue;
                }

                // Create rectangles to represent terrain squares
                sf::RectangleShape tile(sf::Vector2f(mapTileWidth, mapTileHeight));

                // Set color based on tileMap value
                switch (tileMap[i][j]) {
                    case GRASS:
                        tile.setFillColor(GRASS_COLOR);
                        break;
                    case DIRT:
                        tile.setFillColor(DIRT_COLOR);
                        break;
                    case STONE:
                        tile.setFillColor(STONE_COLOR);
                        break;
                    default:
                        tile.setFillColor(SKY_COLOR); // Default color for unknown terrain
                        break;
                }

                // Set position of the tile
                tile.setPosition(posX, posY);

                // Draw the tile
                window.draw(tile);
            }
        }


        window.display();
    }

    return 0;
}



void generate_terrain(int ** tileMap){
     // Create multiple Perlin noise layers with different frequencies and amplitudes
    std::vector<float> frequencies = {0.02f, 0.05f, 0.1f}; // Adjust frequencies for more or fewer hills
    std::vector<float> amplitudes = {60.f, 50.f, 25.f}; // Adjust amplitudes for higher or lower hills
   
    // SEED PERLIN
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(1, 1000000);
    const siv::PerlinNoise::seed_type seed = dist(rng);
    const siv::PerlinNoise perlin(seed);

    // Generate terrain
    for (int j = 0; j < mapCols; ++j) {
        float height = 0.f;

        for (size_t k = 0; k < frequencies.size(); ++k) {
            float perlinValue = perlin.noise1D_01(static_cast<float>(j) * frequencies[k]) * amplitudes[k];
            height += perlinValue;
        }

        int grass_height = static_cast<int>(std::round(height));


        for (int i = 0; i < mapRows; ++i) {
            int diff = std::abs(grass_height - i);

            if (i < grass_height) {
                tileMap[i][j] = SKY;
            } else if (diff <= 0) {
                tileMap[i][j] = GRASS;
            } else if (diff <= 10) {
                tileMap[i][j] = DIRT;
            } else {
                tileMap[i][j] = STONE;
            }
        }
    }
}
