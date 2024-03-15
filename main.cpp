#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

const float SCREEN_WIDTH = 800.f;
const float SCREEN_HEIGHT = 600.f;

const int sizeX = 32;
const int sizeY = 30;
const float tileSize = SCREEN_WIDTH / sizeX;
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

    const float center = sizeY * tileSize / 2;

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

    for (int x = 0; x < sizeX; ++x) {
        for (int y = 0; y < sizeY; ++y) {
            int xPos = x * tileSize;
            int yPos = y * tileSize;

            tile.setPosition(xPos, yPos);

            // Calculate the height of the tile based on Perlin noise
            float noiseValue = noise(x); // Use x coordinate for noise generation
            float height = 100 + noiseValue * 300; // Adjust multiplier for different heights
            
            sf::Color colour;

            if (yPos < height) {
                colour = skyColor;
            } else if (yPos <= height + 25) {
                colour = grassColor;
            } else if (yPos <= height + 75) {
                colour = dirtColor;
            } else {
                colour = stoneColor;
            }
     
            

            tile.setFillColor(colour);


            dot.setPosition(x * tileSize, height);
            window.draw(dot);

            tile.setOutlineColor(sf::Color::Black);
            window.draw(tile);

            std::ostringstream ss;
            if (x == 0) {
                ss <<  y;
            } else if (y == 0) {
                ss <<  x;
            } else {
                continue;
            }
            text.setString(ss.str());
            text.setPosition(x * tileSize + 0.5f * tileSize, y * tileSize + 0.5f * tileSize);
            window.draw(text);
        }
    }

    window.display();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}
