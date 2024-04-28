#ifndef GAME_ACTOR_H
#define GAME_ACTOR_H

#include <SFML/Graphics.hpp>
#include <iostream>


class Game; // Forward declaration of Game class

class IGameActor {
protected:
    sf::Vector2f position       = {0.f, 0.f};
    sf::Vector2f velocity       = {0.f, 0.f};
    sf::Vector2f acceleration   = {0.f, 0.f};

    bool movingLeft     = false;
    bool movingRight    = false;
    bool movingUp       = false;
    bool movingDown     = false;

    Game* game; // Pointer to the Game object

public:
    virtual ~IGameActor() {}

    // Constructor    
    IGameActor(Game* gamePtr) : game(gamePtr) {}

    // Default constructor
    IGameActor() : game(nullptr) {}

    // Update function to be implemented by derived classes
    virtual void update(float dt) = 0;

    // Set position
    virtual void setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }

    // Get position
    virtual sf::Vector2f getPosition() const {
        return position;
    }

    // Draw function to be implemented by derived classes
    virtual void draw(sf::RenderWindow& window) = 0;

    // Set moving flags
    virtual void setMovingLeft(bool moveLeft) = 0;
    virtual void setMovingRight(bool moveRight) = 0;
    virtual void setMovingUp(bool moveUp) = 0;
    virtual void setMovingDown(bool moveDown) = 0;

    // New functions for handling key presses and releases
    virtual void handleKeyPressed(sf::Keyboard::Key key) = 0;
    virtual void handleKeyReleased(sf::Keyboard::Key key) = 0;

};

#endif // GAME_ACTOR_H
