#include "player.h"

#include <iostream>
#include <algorithm>
#include <iostream>
#include "/home/taylor/Desktop/Projects/Game Dev/C++/2D-Terrain-Generation/game.h"


Player::Player(Game* game) : IGameActor(game) {
    setPosition(mapCentreX, 1); 
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
    std::cout << game->name;
    /*sf::Vector2f nextPosition = tileMap->getArrayPosition(position + movement)
    
    if (!tileMap->isCollidingWithTerrain(nextPosition)) {
        position += movement;
    } else {
        // Stop vertical movement if colliding with terrain
        velocity.y = 0.0f;
    }
    */
}

void Player::draw(sf::RenderWindow& window) {
    sf::CircleShape playerShape(10.f); // Example player shape
    playerShape.setPosition(SCREEN_CENTRE_X, SCREEN_CENTRE_Y);
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

int Player::findPlayerStartingY() {
    for (int i = 0; i < mapRows; ++i) {
        //if (tileMap->getTile(i, mapCentreCol) != SKY) 
        return static_cast<int>((i-1) * tileHeight);
    }
    return -1; 
}
