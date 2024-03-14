#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>

const float SCREEN_WIDTH = 800.f;
const float SCREEN_HEIGHT = 600.f;

const int sizeX = 32;
const int sizeY = 30;
const float tileSize = SCREEN_WIDTH / sizeX;
const float borderThickness = 1.f;

//new
int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flat 2D World Generation");
    window.setFramerateLimit(60);

    sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
    tile.setOutlineThickness(borderThickness);

    const float skyHeight = 100.f;
    const float grassHeight = 200.f;
    const float dirtHeight = 300.f;
    const float center = sizeY * tileSize / 2;
    const float stoneHeight = 400.f;

    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        std::cerr << "Failed to load font. Using default font." << std::endl;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(10);
    text.setFillColor(sf::Color::White);

    for (int x = 0; x < sizeX; ++x) {
        for (int y = 0; y < sizeY; ++y) {
            tile.setPosition(x * tileSize, y * tileSize);

            if (y == 0 || x == 0) {
                tile.setFillColor(sf::Color::Red);
            } else if (y * tileSize < skyHeight) {
                tile.setFillColor(sf::Color::Blue);
            } else if (y * tileSize < grassHeight) {
                tile.setFillColor(sf::Color::Green);
            } else if (y * tileSize < dirtHeight) {
                tile.setFillColor(sf::Color(139, 69, 19));
            } else if (y * tileSize < stoneHeight) {
                tile.setFillColor(sf::Color(128, 128, 128));
            }

            tile.setOutlineColor(sf::Color::White);
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
