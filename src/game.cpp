#include "game.h"

Game::Game() : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flat 2D World Generation"),
            playerTexture(),
            tileMap(mapRows, mapCols),
            player(this),
            view(),
            gameActors()
{
    window.setFramerateLimit(60);
    view.setSize(SCREEN_SIZE);

    if (!playerTexture.loadFromFile("Assets/textures/player.png")) {
        std::cerr << "Failed to load player texture!" << std::endl;
        std::exit(1);
    }

    // Add player to gameActors vector
    gameActors.push_back(&player);
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time elapsedTime = clock.restart();
        float deltaTime = elapsedTime.asSeconds();

        handleEvents();
        update(deltaTime);
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyPressed)
            handleKeyPressed(event.key.code);
        else if (event.type == sf::Event::KeyReleased)
            handleKeyReleased(event.key.code);
    }
}

void Game::handleKeyPressed(sf::Keyboard::Key key) {
    for (IGameActor* actor : gameActors){
        actor->handleKeyPressed(key);
    }
}

void Game::handleKeyReleased(sf::Keyboard::Key key) {
    for (IGameActor* actor : gameActors){
        actor->handleKeyReleased(key);
    }

    if (key == sf::Keyboard::Z) {
        view.zoom(0.9f);
    } else if (key == sf::Keyboard::X) {
        view.zoom(1.1f);
    }
}

void Game::update(float deltaTime) {
    for (IGameActor* actor : gameActors){
        actor->update(deltaTime);
    }

    view.setCenter(player.getPosition());
    window.setView(view);
}

void Game::render() {
    window.clear();
    renderTileMap();

    for (IGameActor* actor : gameActors){
        actor->draw(window);
    }

    window.display();
}

void Game::renderTileMap() {
    // Set the view on the render window
    window.setView(view);

    // Get the center and size of the view
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    // Calculate the top-left corner of the view
    sf::Vector2f viewTopLeft(viewCenter.x - viewSize.x / 2, viewCenter.y - viewSize.y / 2);

    // Calculate the starting row and column indices for rendering tiles
    int startRow = static_cast<int>(viewTopLeft.y / tileHeight);
    int startCol = static_cast<int>(viewTopLeft.x / tileWidth);

    // Ensure startRow and startCol are within bounds
    startRow = std::max(0, std::min(startRow, mapRows - 1));
    startCol = std::max(0, std::min(startCol, mapCols - 1));

    // Calculate the ending row and column indices
    int endRow = static_cast<int>((viewTopLeft.y + viewSize.y) / tileHeight) + 1;
    int endCol = static_cast<int>((viewTopLeft.x + viewSize.x) / tileWidth) + 1;

    // Loop through the viewport and render tiles
    for (int row = startRow; row < endRow; ++row) {
        for (int col = startCol; col < endCol; ++col) {
            // Calculate the position of the tile on the screen
            sf::Vector2f tilePosition(col * tileWidth, row * tileHeight);

            // Create and position the tile rectangle shape
            sf::RectangleShape tile(sf::Vector2f(tileWidth, tileHeight));
            tile.setPosition(tilePosition);

            // Set the fill color based on the tile type
            switch (tileMap[row][col]) {
                case SKY:
                    tile.setFillColor(SKY_COLOR);
                    break;
                case GRASS:
                    tile.setFillColor(GRASS_COLOR);
                    break;
                case DIRT:
                    tile.setFillColor(DIRT_COLOR);
                    break;
                case STONE:
                    tile.setFillColor(STONE_COLOR);
                    break;
                default:
                    break;
            }

            // Draw the tile to the window
            window.draw(tile);
        }
    }

    // Reset the view to default
    window.setView(window.getDefaultView());
}

