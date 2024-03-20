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
             player(CENTRE_X, findPlayerStartingRow(tileMap) * tileHeight) {
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
                    tileMap.generateTileMap();
                    player.setPosition(CENTRE_X, findPlayerStartingRow(tileMap) * tileHeight);
                    break;
                case sf::Keyboard::Z:
                    viewportCols *= 1.1;
                    viewportRows *= 1.1;
                    tileWidth = SCREEN_WIDTH / viewportCols;
                    tileHeight = SCREEN_HEIGHT / viewportRows;
                    break;
                case sf::Keyboard::X:
                    viewportCols *= 0.9;
                    viewportRows *= 0.9;
                    tileWidth = SCREEN_WIDTH / viewportCols;
                    tileHeight = SCREEN_HEIGHT / viewportRows;
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
        int viewportRowBegin = (player.getArrayPosition().y - viewportCols / 2) + yOffset;
        int viewportRowEnd = viewportRowBegin + viewportRows;
        int viewportColBegin = (player.getArrayPosition().x - viewportRows / 2) + xOffset;
        int viewportColEnd = viewportColBegin + viewportCols;

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
    }

    int findPlayerStartingRow(TileMap& tileMap) {
        for (int i = 0; i < mapRows; ++i) {
            if (tileMap[i][centreCol] != SKY) // Use getTile to access elements
                return i;
        }
        return -1; // If no suitable row is found
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}
