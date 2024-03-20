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
    

    // Viewport view
    int viewportCols = 32;
    int viewportRows = 24;

    float tileWidth  = SCREEN_WIDTH / viewportCols;
    float tileHeight = SCREEN_HEIGHT / viewportRows;

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
                    player.moveLeft(); // You should have a method in your Player class to handle movement
                } else if (event.key.code == sf::Keyboard::Right){
                    player.moveRight(); // You should have a method in your Player class to handle movement
                } else if (event.key.code == sf::Keyboard::Down){
                    player.moveDown(); // You should have a method in your Player class to handle movement
                } else if (event.key.code == sf::Keyboard::Up){
                    player.moveUp(); // You should have a method in your Player class to handle movement
                }
            }
        }

        window.clear();

        // Update player position
        player.update(deltaTime);

        // Calculate new offsets to keep player in the center
        xOffset = (player.getPosition().x / tileWidth) - viewportCols / 2;
        yOffset = (player.getPosition().y / tileHeight) - viewportRows / 2;

    
        // Render Tilemap
        for (int i = 0, currentRow = yOffset; i < viewportRows; ++i, ++currentRow) {
            for (int j = 0, currentCol = xOffset; j < viewportCols; ++j, ++currentCol) {
                sf::RectangleShape tile(sf::Vector2f(tileWidth, tileHeight));
                tile.setPosition(j * tileWidth, i * tileHeight);

                switch (tileMap.getTile(currentRow, currentCol)) {
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
    if (tileMap.getTile(i, centreCol) != SKY) // Use getTile to access elements
        return i;
}
return -1; // If no suitable row is found
}

