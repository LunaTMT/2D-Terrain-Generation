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

    const float movement_velocity = 200.0f;
    const float gravity = 0.2f; 

public:
    Player(Game* game);

    void handleKeyPressed(sf::Keyboard::Key key) override;
    void handleKeyReleased(sf::Keyboard::Key key) override;

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

    void setMovingLeft(bool moveLeft) override;
    void setMovingRight(bool moveRight) override;
    void setMovingUp(bool moveUp) override;
    void setMovingDown(bool moveDown) override;

    int findPlayerStartingY();
};

#endif // PLAYER_H
