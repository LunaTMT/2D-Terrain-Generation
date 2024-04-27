#ifndef GAME_ACTOR_H
#define GAME_ACTOR_H

#include <SFML/Graphics.hpp>

class Game;

class IGameActor {
protected:
    sf::Vector2f position;
    Game* game;

public:
    IGameActor() : game(nullptr) {}

    virtual ~IGameActor() {}
    IGameActor(Game* gamePtr) : game(gamePtr) {}

    virtual void update(float dt) = 0;

    virtual void setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }

    virtual sf::Vector2f getPosition() const {
        return position;
    }

    virtual void draw(sf::RenderWindow& window) = 0;

    virtual void setMovingLeft(bool moveLeft) = 0;
    virtual void setMovingRight(bool moveRight) = 0;
    virtual void setMovingUp(bool moveUp) = 0;
    virtual void setMovingDown(bool moveDown) = 0;

    // New functions for handling key presses and releases
    virtual void handleKeyPressed(sf::Keyboard::Key key) = 0;
    virtual void handleKeyReleased(sf::Keyboard::Key key) = 0;
};

#endif // GAME_ACTOR_H
