#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Platform.hpp"
#include <vector>

class Game {
public:
    Game(sf::RenderWindow& win);
    bool run();

private:
    sf::RenderWindow& window;
    sf::View view;
    Player player;
    std::vector<Platform> platforms;
    sf::Clock clock;
    bool isRunning = true;

    // return to main
    sf::Font font;
    sf::Text returnText;


    void processEvents();
    void update(float dt);
    void render();
    void updateView();



};
