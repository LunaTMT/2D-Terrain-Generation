#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <random>
#include <unordered_map>
#include "PerlinNoise.hpp" // Include the Perlin noise header
#include "globals.h"
#include "player.h"


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

    // Load player texture
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("Assets/textures/player.png")) {
        std::cerr << "Failed to load player texture!" << std::endl;
        return 1;
    }

    // Initialize player
    Player player(0, 0); // Initialize player at position (0, 0)


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

    int xOffset = 0;
    int yOffset = 0;

    int i = 0;

    sf::Clock clock;
    float deltaTime = 0.0f;

    sf::Time elapsedTime = clock.restart();
    deltaTime = elapsedTime.asSeconds();



    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::Space) {
                    generateTileMap(tileMap);
                    std::cout << "Generating new " << i << std::endl;
                    i++;

                } else if (event.key.code == sf::Keyboard::Z) {
                    viewportCols *= 1.1;
                    viewportRows *= 1.1;
                    tileWidth = SCREEN_WIDTH / viewportCols;
                    tileHeight = SCREEN_HEIGHT / viewportRows;
                    std::cout << "Increase " << i << std::endl;

                } else if (event.key.code == sf::Keyboard::X) {
                    viewportCols *= 0.9;
                    viewportRows *= 0.9;
                    tileWidth = SCREEN_WIDTH / viewportCols;
                    tileHeight = SCREEN_HEIGHT / viewportRows;
                    i++;
                    std::cout << "Decrease " << i << std::endl;
                } else if (event.key.code == sf::Keyboard::Left){
                    xOffset--;
                    i++;
                    std::cout << "LEFT " << i << std::endl;
                } else if (event.key.code == sf::Keyboard::Right){
                    xOffset++;
                    i++;
                    std::cout << "RIGHT " << i << std::endl;
                } else if (event.key.code == sf::Keyboard::Down){
                    yOffset++;
                    i++;
                    std::cout << "DOWN " << i << std::endl;
                } else if (event.key.code == sf::Keyboard::Up){
                    yOffset--;
                    i++;
                    std::cout << "UP " << i << std::endl;
                }
            }
        }

        window.clear();

        int playerX = (viewportCols >> 1) * tileWidth;
        int playerY = (viewportRows >> 1) * tileHeight;

        float x = player.getPosition().x;
        float y = player.getPosition().y;

        //centering viewport for given screen size
        int startCol = player.getPosition().x - (viewportCols >> 1) + xOffset;
        int endCol = startCol + viewportCols;

        int startRow = (player.getPosition().y / tileHeight) + yOffset;
        int endRow = startRow + viewportRows;

       

        player.setPosition(playerX, playerY);
        player.update(deltaTime);


        //Render Tilemap
        for (int i = 0, currentRow = startRow; currentRow < endRow; ++i, ++currentRow) {
            for (int j = 0, currentCol = startCol; currentCol < endCol; ++j, ++currentCol) {

                sf::RectangleShape tile(sf::Vector2f(tileWidth, tileHeight));
                tile.setPosition(j * tileWidth, i * tileHeight);

                switch (tileMap[currentRow][currentCol]) {
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

        player.draw(window);

        window.display();
    }

    dealocateTileMap(tileMap);
    return 0;
}

void generateTileMap(int ** tileMap) {
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
