#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include <unordered_map>
#include "globals.h"
#include "player.h"
#include "tileMap.h"

class Game {
public:
    Game() : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flat 2D World Generation"),
             playerTexture(),
             tileMap(mapRows, mapCols),
             player(mapCentreX, findPlayerStartingRow(tileMap) * tileHeight) {
        window.setFramerateLimit(60);
        if (!playerTexture.loadFromFile("Assets/textures/player.png")) {
            std::cerr << "Failed to load player texture!" << std::endl;
            std::exit(1);
        }
    }

    void run() {
        sf::Clock clock;
        while (window.isOpen()) {
            sf::Time elapsedTime = clock.restart();
            float deltaTime = elapsedTime.asSeconds();

            handleEvents();
            update(deltaTime);
            render();
        }
    }

private:
    sf::RenderWindow window;
    sf::Texture playerTexture;
    TileMap tileMap;
    Player player;
    int xOffset = 0;
    int yOffset = 0;

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else
                handleEvent(event);
        }
    }

    void handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Space:
                std::cout << "Regenerating " << i << std::endl;
                    tileMap.generateTileMap();
                    player.setPosition(mapCentreX, findPlayerStartingRow(tileMap) * tileHeight);
                    i++;
                    break;
                case sf::Keyboard::Z:
                    std::cout << "increasing viewport" << std::endl;
                    viewportCols *= 1.1;
                    viewportRows *= 1.1;
                    tileWidth = SCREEN_WIDTH / viewportCols;
                    tileHeight = SCREEN_HEIGHT / viewportRows;
                    player.setPosition(player.getPosition().x, findPlayerStartingRow(tileMap) * tileHeight);
                    break;
                case sf::Keyboard::X:
                    std::cout << "decreasing viewport" << std::endl;
                    viewportCols *= 0.9;
                    viewportRows *= 0.9;
                    tileWidth  = SCREEN_WIDTH / viewportCols;
                    tileHeight = SCREEN_HEIGHT / viewportRows;
                    player.setPosition(player.getPosition().x, findPlayerStartingRow(tileMap) * tileHeight);
                    break;
                case sf::Keyboard::Left:
                    xOffset--;
                    break;
                case sf::Keyboard::Right:
                    xOffset++;
                    break;
                case sf::Keyboard::Down:
                    yOffset++;
                    break;
                case sf::Keyboard::Up:
                    yOffset--;
                    break;
                default:
                    break;
            }
        }
    }

    void update(float deltaTime) {
        player.update(deltaTime);
    }

    void render() {
        window.clear();
        renderTileMap();
        player.draw(window);
        window.display();
    }

    void renderTileMap() {
        // Calculate the starting row and column indices for rendering tiles
        int startRow = player.getArrayPosition().y - (viewportRows >> 1) + yOffset;
        int startCol = player.getArrayPosition().x - (viewportCols >> 1) + xOffset;

        // Calculate the ending row and column indices
        int endRow = startRow + viewportRows;
        int endCol = startCol + viewportCols;

        // Loop through the viewport and render tiles
        for (int i = 0, row = startRow; row < endRow; ++i, ++row) {
            for (int j = 0, col = startCol; col < endCol; ++j, ++col) {
                // Check if the current row and column are within bounds of the tile map
                if (row >= 0 && row < mapRows && col >= 0 && col < mapCols) {
                    sf::RectangleShape tile(sf::Vector2f(tileWidth, tileHeight));
                    tile.setPosition(j * tileWidth, i * tileHeight);
                    
                    switch (tileMap[row][col]) {
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
        }
    }

    int findPlayerStartingRow(TileMap& tileMap) {
        for (int i = 0; i < mapRows; ++i) {
            if (tileMap[i][mapCentreCol] != SKY) // Use getTile to access elements
                return i-1;
        }
        return -1; // If no suitable row is found
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}
