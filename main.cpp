#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include <unordered_map>
// Include the Perlin noise header
#include "globals.h"
#include "player.h"
#include "tileMap.h"


int findPlayerStartingRow(TileMap& tileMap);

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flat 2D World Generation");
    window.setFramerateLimit(60);

    // Load player texture
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("Assets/textures/player.png")) {
        std::cerr << "Failed to load player texture!" << std::endl;
        return 1;
    }


    //The following 2D array is dynamically created on the heap for large array sizes
    
    TileMap tileMap(mapRows, mapCols);
    
    int xOffset = 0;
    int yOffset = 0;

    int i = 0;
    // Initialize player
    
    Player player(CENTRE_X, findPlayerStartingRow(tileMap) * tileHeight); // Initialize player at position (0, 0)


    sf::Clock clock;
    float deltaTime = 0.0f;

    while (window.isOpen()) {

        sf::Time elapsedTime = clock.restart();
        deltaTime = elapsedTime.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::Space) {
                    tileMap.generateTileMap(); 
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
                    //player.moveLeft(); 
                    xOffset--; // Decrement xOffset when moving left
                } else if (event.key.code == sf::Keyboard::Right){
                    //player.moveRight(); 
                    xOffset++; // Increment xOffset when moving right
                } else if (event.key.code == sf::Keyboard::Down){
                    //player.moveDown(); 
                    yOffset++; // Increment yOffset when moving down
                } else if (event.key.code == sf::Keyboard::Up){
                    //player.moveUp(); 
                    yOffset--; // Decrement yOffset when moving up
                }
            }
        }

        window.clear();

        // Update player position
        player.update(deltaTime);

        // Calculate new offsets to keep player in the center
        int viewportRowBegin = player.getArrayPosition().y - viewportCols / 2;
        int viewportRowEnd = viewportRowBegin + viewportRows;

        int viewportColBegin = player.getArrayPosition().x - viewportRows / 2;
        int viewportColEnd = viewportColBegin + viewportCols;

        // Render Tilemap
        for (int i = 0, currentRow = viewportRowBegin; i < viewportRowEnd; ++i, ++currentRow) {
            for (int j = 0, currentCol = viewportColBegin; j < viewportColEnd; ++j, ++currentCol) {
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

    return 0;
}


int findPlayerStartingRow(TileMap& tileMap){
for (int i = 0; i < mapRows; ++i){
    if (tileMap[i][centreCol] != SKY) // Use getTile to access elements
        return i;
}
return -1; // If no suitable row is found
}

