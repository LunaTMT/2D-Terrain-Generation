#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

const float SCREEN_WIDTH = 800.f;
const float SCREEN_HEIGHT = 600.f;

const int COLS = 32; // Renamed sizeX to COLS
const int ROWS = 24; // Renamed sizeY to ROWS
const float tileSize = SCREEN_WIDTH / COLS; // Updated tileSize calculation
const float borderThickness = 1.f;


// Define parameters for generating terrain using Perlin noise
const float noiseScale = 0.1f;
const float noiseOffset = 100.f;

float noise(float x) {
    // Basic implementation of 1D Perlin noise
    x = x * noiseScale + noiseOffset;
    return std::sin(x) * 0.5f + 0.5f;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flat 2D World Generation");
    window.setFramerateLimit(60);

    sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
    tile.setOutlineThickness(borderThickness);

    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        std::cerr << "Failed to load font. Using default font." << std::endl;
    }
    
    sf::Color skyColor(135, 206, 250); // Sky Blue
    sf::Color grassColor(34, 139, 34); // Dark Green
    sf::Color dirtColor(139, 69, 19);  // Brown
    sf::Color stoneColor(169, 169, 169); // Dark Gray
    
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(10);
    text.setFillColor(sf::Color::Black);

    sf::CircleShape dot(2.f); // Define a small circle shape for the dots
    dot.setFillColor(sf::Color::Red); // Set the color of the dots

    float viewOffsetX = 0.f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                // Adjust view offset based on arrow keys or WASD keys
                switch (event.key.code) {
                    case sf::Keyboard::Left:
                    case sf::Keyboard::A:
                        viewOffsetX -= tileSize;
                        break;
                    case sf::Keyboard::Right:
                    case sf::Keyboard::D:
                        viewOffsetX += tileSize;
                        break;
                    default:
                        break;
                }
            }
        }

        window.clear();

        for (int x = 0; x <= COLS; ++x) { // Add 2 extra tiles on each side
            for (int y = 0; y <= ROWS; ++y) {
                int xPos = x  * tileSize; // Adjust x position for additional tiles
                int yPos = y * tileSize;

                tile.setPosition(xPos, yPos);

                // Calculate the height of the tile based on Perlin noise
                float noiseValue = noise(x + viewOffsetX / tileSize); // Use adjusted x coordinate for noise generation
                float height = 100 + noiseValue * 300; // Adjust multiplier for different heights
                
                sf::Color colour;

                if (yPos < height) {
                    colour = skyColor;
                } else if (yPos <= height + 50) {
                    colour = grassColor;
                } else if (yPos <= height + 100) {
                    colour = dirtColor;
                } else {
                    colour = stoneColor;
                }

                tile.setFillColor(colour);

                dot.setPosition(xPos, height);
                window.draw(dot);

                tile.setOutlineColor(sf::Color::Black);
                window.draw(tile);

                std::ostringstream ss;
                if (x == 0) {
                    ss <<  y+1;
                } else if (y == 0) {
                    ss <<  x+1 + viewOffsetX / tileSize; // Adjust x position for additional tiles
                } else {
                    continue;
                }
                text.setString(ss.str());
                text.setPosition(xPos + 0.5f * tileSize, yPos + 0.5f * tileSize);
                window.draw(text);
            }
        }

        window.display();
    }

    return 0;
}
