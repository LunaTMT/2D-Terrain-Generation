#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>

// Constants
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

const float CENTRE_X = SCREEN_WIDTH >> 1;
const float CENTRE_Y = SCREEN_HEIGHT >> 1;

// Tile map dimensions
const int mapRows = 1200;
const int mapCols = 4200;

const int centreRow = mapRows >> 1;
const int centreCol = mapCols >> 1;

// Colours
const sf::Color SKY_COLOR(135, 206, 250);    // Sky Blue
const sf::Color GRASS_COLOR(34, 139, 34);    // Dark Green
const sf::Color DIRT_COLOR(139, 69, 19);     // Brown
const sf::Color STONE_COLOR(169, 169, 169);  // Dark Gray

enum Terrain {
    SKY,
    GRASS,
    DIRT,
    STONE
};

#endif // CONSTANTS_H