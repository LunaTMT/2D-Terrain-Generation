#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <memory>

#include "globals.h"
#include "player.h"
#include "tileMap.h"

#include "ICommand.h"
#include "MovementCommands.h"
#include "StopMovementCommands.h"

class Game {
public:
    Game();
    void run();

    int name = 1;
    sf::RenderWindow window;
    sf::Texture playerTexture;
    TileMap tileMap;
    Player player;
    sf::View view;
    std::vector<IGameActor*> gameActors;

private:
    void handleEvents();
    void handleKeyPressed(sf::Keyboard::Key key);
    void handleKeyReleased(sf::Keyboard::Key key);
    void update(float deltaTime);
    void render();
    void renderTileMap();
    
};
#endif // GAME_H

