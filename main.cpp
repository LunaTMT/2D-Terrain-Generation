#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <random>

const float SCREEN_WIDTH = 800.f;
const float SCREEN_HEIGHT = 600.f;

const int COLS = 32; // Renamed sizeX to COLS
const int ROWS = 24; // Renamed sizeY to ROWS
const float tileSize = SCREEN_WIDTH / COLS; // Updated tileSize calculation
const float borderThickness = 1.f;

// Define parameters for generating terrain using Perlin noise
const float noiseScale = 0.1f;
const float noiseOffset = 100.f;

// Linearly interpolate between a and b based on weight t
float lerp(float a, float b, float t) {
    return a + t * (b - a);
}

// Compute the dot product of the gradient vector and the distance vector
float dotGridGradient(int ix, int iy, float x, float y, float gradient) {
    std::default_random_engine generator(ix * 32749 + iy * 65153); // Use ix and iy as the seed for the random engine
    std::uniform_real_distribution<float> distribution(-1.f, 1.f);

    float dx = x - ix;
    float dy = y - iy;
    float randomGradientX = distribution(generator); // Random value between -1 and 1 for x
    float randomGradientY = distribution(generator); // Random value between -1 and 1 for y

    return dx * (gradient + randomGradientX) + dy * randomGradientY;
}

// Compute the noise value at a given position (x, y) using 2D Perlin noise with randomness
float perlinNoise(float x, float y, float viewOffsetX) {
    int x0 = static_cast<int>(x);
    int x1 = x0 + 1;
    int y0 = static_cast<int>(y);
    int y1 = y0 + 1;

    float sx = x - x0;
    float sy = y - y0;

    // Compute dot products of gradient vectors and distance vectors with added randomness
    float n00 = dotGridGradient(x0, y0, x, y, std::sin(x0 + y0) * 0.5f + 0.5f + viewOffsetX * 0.1f); // Adding randomness based on view offset
    float n01 = dotGridGradient(x0, y1, x, y, std::sin(x0 + y1) * 0.5f + 0.5f + viewOffsetX * 0.1f); // Adding randomness based on view offset
    float n10 = dotGridGradient(x1, y0, x, y, std::sin(x1 + y0) * 0.5f + 0.5f + viewOffsetX * 0.1f); // Adding randomness based on view offset
    float n11 = dotGridGradient(x1, y1, x, y, std::sin(x1 + y1) * 0.5f + 0.5f + viewOffsetX * 0.1f); // Adding randomness based on view offset

    // Interpolate along x-axis
    float ix0 = lerp(n00, n10, sx);
    float ix1 = lerp(n01, n11, sx);

    // Interpolate along y-axis
    return lerp(ix0, ix1, sy);
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

             // Calculate the height of the tile based on 2D Perlin noise
            float noiseValue = perlinNoise(std::abs((x + viewOffsetX / tileSize) * noiseScale),  noiseScale, std::abs(viewOffsetX));
            float height = 400 + noiseValue * 500; // Adjust multiplier for different heights

            for (int y = 0; y <= ROWS; ++y) {
                float xPos = x * tileSize; // Adjust x position for additional tiles
                float yPos = y * tileSize;

                tile.setPosition(xPos, yPos);

               

                sf::Color colour;

                if (yPos < height) {
                    colour = skyColor;
                } else if (yPos <= height + 25) {
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
