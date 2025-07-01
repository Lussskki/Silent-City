#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Platform.hpp"
#include <vector>

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    Player player;
    std::vector<Platform> platforms;
    sf::Clock clock;

    void processEvents();
    void update(float dt);
    void render();
};
