#ifndef GAME_ACTOR_H
#define GAME_ACTOR_H

#include <SFML/Graphics.hpp>


class IGameActor {
protected:
    sf::Vector2f position;

public:
    virtual ~IGameActor() {}

    virtual void update(float dt) = 0;

    virtual void setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }

    virtual sf::Vector2f getPosition() const {
        return position;
    }

    virtual void draw(sf::RenderWindow& window) = 0;

    // Declare these functions as virtual
    virtual void setMovingLeft(bool moveLeft) = 0;
    virtual void setMovingRight(bool moveRight) = 0;
    virtual void setMovingUp(bool moveUp) = 0;
    virtual void setMovingDown(bool moveDown) = 0;
};

#endif // GAME_ACTOR_H
