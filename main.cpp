#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

int width = 800;
int height = 600;

int cols = 32; 
int tileSize = width / cols;
int rows = height / tileSize;
int test = 0;

// Function to generate a random SFML color
sf::Color getRandomColor() {
    // Generate random values for red, green, and blue components
    sf::Uint8 red = std::rand() % 256;     // Random value for red component
    sf::Uint8 green = std::rand() % 256;   // Random value for green component
    sf::Uint8 blue = std::rand() % 256;    // Random value for blue component

    // Create and return the random color
    return sf::Color(red, green, blue);
}

int main(){

    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(width, height), "2D Terrain Generation");

    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        window.clear();

        for (int row = 0; row < rows; ++row){
            for (int col = 0; col < cols; ++col){
                sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
                tile.setPosition(col * tileSize, row * tileSize);
                tile.setFillColor(sf::Color::White);
                tile.setOutlineThickness(1); // 1 pixel thick outline
                tile.setOutlineColor(sf::Color::Black); // Black outline color
                window.draw(tile);
            }
        }        

        window.display();

    }
    return 0;
}
