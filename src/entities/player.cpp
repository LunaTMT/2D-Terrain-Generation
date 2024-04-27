#include "player.h"
#include <algorithm>
#include <iostream>

Player::Player(float x, float y, Game* game) : IGameActor(game), velocity(0.f, 0.f), acceleration(0.f, 0.f), 
                                     movingLeft(false), movingRight(false), movingUp(false), movingDown(false) {
    setPosition(x, y); // Use setPosition method from IGameActor to set initial position
}


void Player::handleKeyPressed(sf::Keyboard::Key key) {
    auto it = commands.find(key);
    if (it != commands.end()) {
        it->second->execute(*this);
    }
}

 void Player::handleKeyReleased(sf::Keyboard::Key key) {
    auto it = releaseCommands.find(key);
    if (it != releaseCommands.end()) {
        it->second->execute(*this);
    }
 }

void Player::update(float dt) {
    // Apply gravity
    acceleration.y = gravity;

    // Apply movement based on flags
    if (movingLeft) {
        velocity.x = -movement_velocity; // Adjust the speed as needed
    } else if (movingRight) {
        velocity.x = movement_velocity; // Adjust the speed as needed
    } else {
        velocity.x = 0.0f; // Stop horizontal movement if no key is pressed
    }

    if (movingUp) {
        velocity.y = -movement_velocity; // Adjust the speed as needed
    } else if (movingDown) {
        velocity.y = movement_velocity; // Adjust the speed as needed
    } else {
        velocity.y = 0.0f; // Stop vertical movement if no key is pressed
    }

    // Update velocity based on acceleration
    velocity += acceleration * dt;

    // Clamp velocity to maximum falling speed
    velocity.y = std::min(velocity.y, max_fall_speed);

    sf::Vector2f movement = velocity * dt;

    // Check for collisions with terrain
    sf::Vector2f nextPosition = position + movement;
    if (!isCollidingWithTerrain(nextPosition)) {
        // Update position if no collision
        position += movement;
    } else {
        // Stop vertical movement if colliding with terrain
        velocity.y = 0.0f;
    }
}

bool Player::isCollidingWithTerrain(sf::Vector2f nextPosition) const {
    return false;
}



void Player::applyForce(sf::Vector2f force) {
    acceleration += force;
}

sf::Vector2f Player::getArrayPosition() const {
    // .x - col
    // .y - row
    return sf::Vector2(position.x / tileWidth, position.y / tileHeight);
}

sf::Vector2f Player::getArrayPosition(float x, float y) const {
    // .x - col
    // .y - row
    return sf::Vector2(x / tileWidth, y / tileHeight);
}

void Player::draw(sf::RenderWindow& window) {
    sf::CircleShape playerShape(10.f); // Example player shape
    playerShape.setPosition(SCREEN_CENTRE_X, SCREEN_CENTRE_Y);
    //std::cout << position.x - cameraPosition.x<< "  " << position.y - cameraPosition.y << std::endl;
    playerShape.setFillColor(sf::Color::Red); // Set player color
    window.draw(playerShape);
}

void Player::setMovingLeft(bool moveLeft) {
    movingLeft = moveLeft;
}

void Player::setMovingRight(bool moveRight) {
    movingRight = moveRight;
}

void Player::setMovingUp(bool moveUp) {
    movingUp = moveUp;
}

void Player::setMovingDown(bool moveDown) {
    movingDown = moveDown;
}
