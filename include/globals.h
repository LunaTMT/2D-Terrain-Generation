// In globals.h

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>

// Constants
const float SCREEN_WIDTH = 800.f;
const float SCREEN_HEIGHT = 600.f;

const sf::Vector2f SCREEN_SIZE(SCREEN_WIDTH, SCREEN_HEIGHT);


const float SCREEN_CENTRE_X = SCREEN_WIDTH / 2;
const float SCREEN_CENTRE_Y = SCREEN_HEIGHT / 2;


// Variable definitions
inline int viewportCols = 32;
inline int viewportRows = 24;

inline float tileWidth = SCREEN_WIDTH / viewportCols;
inline float tileHeight = SCREEN_HEIGHT / viewportRows;

inline int xOffset = 0;
inline int yOffset = 0;

inline int i = 0;


// Tile map dimensions
const int mapRows = 1200;
const int mapCols = 4200;

const int mapCentreRow = mapRows >> 1;
const int mapCentreCol = mapCols >> 1;

const int mapCentreX = mapCentreCol * tileHeight;
const int mapCentreY = mapCentreRow * tileWidth;




// Colours
const sf::Color SKY_COLOR(135, 206, 250);    // Sky Blue
const sf::Color GRASS_COLOR(34, 139, 34);    // Dark Green
const sf::Color DIRT_COLOR(139, 69, 19);     // Brown
const sf::Color STONE_COLOR(169, 169, 169);  // Dark Gray

enum Terrain {
    SKY,
    GRASS,
    DIRT,
    STONE,
    EMPTY
};

#endif // CONSTANTS_H
