#include "player.h"
#include <iostream>

Player::Player(float x, float y) : position(x, y), velocity(0.f, 0.f), acceleration(0.f, 0.f) {}

void Player::update(float dt) {
    // Apply gravity
    acceleration.y += gravity;

    // Update velocity
    //velocity += acceleration * dt;

    // Update position
    //position += velocity * dt;
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

sf::Vector2f Player::getArrayPosition() const {
    return sf::Vector2(position.x / tileWidth, position.y / tileHeight);
}



void Player::draw(sf::RenderWindow& window) {
    sf::CircleShape playerShape(10.f); // Example player shape
    playerShape.setPosition(position);
    playerShape.setFillColor(sf::Color::Red); // Set player color
    window.draw(playerShape);
}

void Player::moveLeft() {
    velocity.x = -20.0f; // Adjust the speed as needed
}

void Player::moveRight() {
    velocity.x = 20.0f; // Adjust the speed as needed
}

void Player::moveUp() {
    velocity.y = -20.0f; // Adjust the speed as needed
}

void Player::moveDown() {
    velocity.y = 20.0f; // Adjust the speed as needed
}
