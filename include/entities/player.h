#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "IGameActor.h"
#include "globals.h"

class Player : public IGameActor {
private:
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    bool movingLeft = false;
    bool movingRight = false;
    bool movingUp = false;
    bool movingDown = false;
    
    const float movement_velocity = 200.0f;
    const float gravity = 0.2f; 

public:
    Player(float x, float y);

    void update(float dt) override;

    void applyForce(sf::Vector2f force);

    sf::Vector2f getArrayPosition() const;

    void draw(sf::RenderWindow& window) override;

    // Override the methods from the base class
    void setMovingLeft(bool moveLeft) override;
    void setMovingRight(bool moveRight) override;
    void setMovingUp(bool moveUp) override;
    void setMovingDown(bool moveDown) override;
};

#endif // PLAYER_H
