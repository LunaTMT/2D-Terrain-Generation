#include <SFML/Graphics.hpp>
#include "globals.h"


class Player {

private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    const float gravity = 0.2f; // Adjust gravity strength as needed
    sf::Color color; // Player color

public:
    Player(float x, float y, sf::Color playerColor) : position(x, y), velocity(0.f, 0.f), acceleration(0.f, 0.f), color(playerColor) {}

    void update(float dt) {
        // Apply gravity
        acceleration.y += gravity;

        // Update velocity
        velocity += acceleration * dt;

        // Update position
        position += velocity * dt;

        // Reset acceleration for next frame
        acceleration = sf::Vector2f(0.f, 0.f);
    }

    void applyForce(sf::Vector2f force) {
        acceleration += force;
    }

    void setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }

    sf::Vector2f getPosition() const {
        return position;
    }

    void draw(sf::RenderWindow& window) {
        sf::CircleShape playerShape(10.f); // Example player shape
        playerShape.setPosition(position);
        playerShape.setFillColor(color); // Set player color
        window.draw(playerShape);
    }
};
