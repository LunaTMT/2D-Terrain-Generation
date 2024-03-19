#include "player.h"
#include <iostream>


Player::Player(float x, float y) : position(x, y), velocity(0.f, 0.f), acceleration(0.f, 0.f) {}

void Player::update(float dt) {
    // Apply gravity
    std::cout << "updating " << std::endl;
    acceleration.y += gravity;

    // Update velocity
    velocity += acceleration * dt;

    // Update position
    position += velocity * dt;

    // Reset acceleration for next frame
    acceleration = sf::Vector2f(0.f, 0.f);
}

void Player::applyForce(sf::Vector2f force) {
    acceleration += force;
}

void Player::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

sf::Vector2f Player::getPosition() const {
    return position;
}

void Player::draw(sf::RenderWindow& window) {
    sf::CircleShape playerShape(10.f); // Example player shape
    playerShape.setPosition(position);

    // Print position components separately
    std::cout << "Player Position: (" << position.x << ", " << position.y << ")" << std::endl;

    playerShape.setFillColor(sf::Color::Red); // Set player color
    window.draw(playerShape);
    std::cout << "Drew player" << std::endl;
}