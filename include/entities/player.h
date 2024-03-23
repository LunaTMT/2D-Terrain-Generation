#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "globals.h"

class Player {
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    bool movingLeft = false;
    bool movingRight = false;
    bool movingUp = false;
    bool movingDown = false;
    
    const float movement_velocity = 200.0f;
    const float gravity = 0.2f; // Adjust gravity strength as needed

public:
    Player(float x, float y);

    void update(float dt);

    void applyForce(sf::Vector2f force);

    void setPosition(float x, float y);

    sf::Vector2f getPosition() const;
    sf::Vector2f getArrayPosition() const;

    void draw(sf::RenderWindow& window);

    void setMovingLeft(bool moveLeft);

    void setMovingRight(bool moveRight);

    void setMovingUp(bool moveUp);

    void setMovingDown(bool moveDown);
};

#endif // PLAYER_H
