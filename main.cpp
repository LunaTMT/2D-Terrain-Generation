#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <random>
#include <unordered_map>
#include "PerlinNoise.hpp" // Include the Perlin noise header

// Constants
const float SCREEN_WIDTH = 800.f;
const float SCREEN_HEIGHT = 600.f;

// Tile map dimensions
const int mapRows = 1200;
const int mapCols = 4200;

/*

Small: 4200x1200
Medium: 6400x1800
Large: 8400x2400

*/


// Colours
const sf::Color SKY_COLOR(135, 206, 250);    // Sky Blue
const sf::Color GRASS_COLOR(34, 139, 34);    // Dark Green
const sf::Color DIRT_COLOR(139, 69, 19);     // Brown
const sf::Color STONE_COLOR(169, 169, 169);  // Dark Gray

// Terrain enum
enum Terrain {
    SKY,
    GRASS,
    DIRT,
    STONE
};

// function prototypes
void generateTileMap(int** tileMap);
void renderTileMap(sf::RenderWindow& window, int** tileMap);
void dealocateTileMap(int** tileMap);

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flat 2D World Generation");
    window.setFramerateLimit(60);

    sf::CircleShape dot(2.f);
    dot.setFillColor(sf::Color::Red);

    //The following 2D array is dynamically created on the heap for large array sizes
    int** tileMap = new int*[mapRows];
    for (int i = 0; i < mapRows; ++i) {
        tileMap[i] = new int[mapCols];
    }
    generateTileMap(tileMap);

    // Viewport view
    int viewportCols = 32;
    int viewportRows = 24;

    float tileWidth  = SCREEN_WIDTH / viewportCols;
    float tileHeight = SCREEN_HEIGHT / viewportRows;

    int i = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::Space) {
                    generateTileMap(tileMap);
                    std::cout << "Generating " << i << std::endl;
                    i++;

                } else if (event.key.code == sf::Keyboard::Z) {
                    viewportCols *= 1.1;
                    viewportRows *= 1.1;
                    tileWidth = SCREEN_WIDTH / viewportCols;
                    tileHeight = SCREEN_HEIGHT / viewportRows;
                    std::cout << "Increase " << std::endl;

                } else if (event.key.code == sf::Keyboard::X) {
                    viewportCols *= 0.9;
                    viewportRows *= 0.9;
                    tileWidth = SCREEN_WIDTH / viewportCols;
                    tileHeight = SCREEN_HEIGHT / viewportRows;
                    std::cout << "Decrease " << std::endl;
                }
            }
        }

        window.clear();

        //centering viewport for given screen size
        int startCol = (mapCols >> 1) - (viewportCols >> 1);
        int endCol = startCol + viewportCols;

        for (int i = 0; i < viewportRows; ++i) {
            for (int j = 0, currentCol = startCol; currentCol < endCol; ++j, ++currentCol) {

                // Draw black border rectangle
                sf::RectangleShape borderRect(sf::Vector2f(tileWidth, tileHeight));
                borderRect.setPosition(j * tileWidth, i * tileHeight);
                borderRect.setFillColor(sf::Color::Black);
                window.draw(borderRect);


                sf::RectangleShape tile(sf::Vector2f(tileWidth - 1, tileHeight - 1));
                tile.setPosition(j * tileWidth, i * tileHeight);

                switch (tileMap[i+50][currentCol]) {
                    case SKY:
                        tile.setFillColor(SKY_COLOR);
                        break;
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
                        break;
                }

                window.draw(tile);
            }
        }

        window.display();
    }

    dealocateTileMap(tileMap);
    return 0;
}

void generateTileMap(int ** tileMap) {
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
        //Gets the noise value for col height
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

void dealocateTileMap(int** tileMap) {
    for (int i = 0; i < mapRows; ++i) {
        delete[] tileMap[i];
    }
    delete[] tileMap;
}
