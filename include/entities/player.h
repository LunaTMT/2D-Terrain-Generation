#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "IGameActor.h"
#include "globals.h"
#include <memory> 
#include "MovementCommands.h"
#include "StopMovementCommands.h"

class Player : public IGameActor {
private:
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    
    std::unordered_map<sf::Keyboard::Key, std::shared_ptr<ICommand>> commands = {
        {sf::Keyboard::Left,  std::make_shared<MoveLeftCommand>()},
        {sf::Keyboard::Right, std::make_shared<MoveRightCommand>()},
        {sf::Keyboard::Up,    std::make_shared<MoveUpCommand>()},
        {sf::Keyboard::Down,  std::make_shared<MoveDownCommand>()}
    };

    std::unordered_map<sf::Keyboard::Key, std::shared_ptr<ICommand>> releaseCommands {
        {sf::Keyboard::Left,  std::make_shared<StopMoveLeftCommand>()},
        {sf::Keyboard::Right, std::make_shared<StopMoveRightCommand>()},
        {sf::Keyboard::Up,    std::make_shared<StopMoveUpCommand>()},
        {sf::Keyboard::Down,  std::make_shared<StopMoveDownCommand>()}
    };

    bool movingLeft = false;
    bool movingRight = false;
    bool movingUp = false;
    bool movingDown = false;

    const float movement_velocity = 200.0f;
    const float gravity = 0.2f; 

public:
    Player(float x, float y, Game* game);

    void handleKeyPressed(sf::Keyboard::Key key) override;
    void handleKeyReleased(sf::Keyboard::Key key) override;


    void update(float dt) override;
    bool isCollidingWithTerrain(sf::Vector2f nextPosition) const;

    void applyForce(sf::Vector2f force);

    sf::Vector2f getArrayPosition() const;
    sf::Vector2f getArrayPosition(float x, float y) const;

    void draw(sf::RenderWindow& window) override;

    // Override the methods from the base class
    void setMovingLeft(bool moveLeft) override;
    void setMovingRight(bool moveRight) override;
    void setMovingUp(bool moveUp) override;
    void setMovingDown(bool moveDown) override;
};

#endif // PLAYER_H
