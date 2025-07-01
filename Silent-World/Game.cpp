#include "Game.hpp"
#include <fstream>
#include <string>

Game::Game()
    : window(sf::VideoMode(800, 600), "Silent World")
{
    platforms.push_back(Platform(sf::Vector2f(170.f, 550.f), sf::Vector2f(100.f, 20.f), sf::Color::Red));    // red
    platforms.push_back(Platform(sf::Vector2f(600.f, 550.f), sf::Vector2f(200.f, 20.f), sf::Color::Blue));   // blue
    platforms.push_back(Platform(sf::Vector2f(400.f, 500.f), sf::Vector2f(150.f, 20.f), sf::Color::Yellow));  // green

    // second line 
    platforms.push_back(Platform(sf::Vector2f(170.f, 450.f), sf::Vector2f(100.f, 20.f), sf::Color::Magenta));    // magneta
    platforms.push_back(Platform(sf::Vector2f(600.f, 450.f), sf::Vector2f(200.f, 20.f), sf::Color::Blue));   // blue
    platforms.push_back(Platform(sf::Vector2f(400.f, 400.f), sf::Vector2f(150.f, 20.f), sf::Color::Yellow));  // green

    // third line 
    platforms.push_back(Platform(sf::Vector2f(170.f, 350.f), sf::Vector2f(100.f, 20.f), sf::Color::Magenta));    // magneta
    platforms.push_back(Platform(sf::Vector2f(600.f, 350.f), sf::Vector2f(200.f, 20.f), sf::Color::Blue));   // blue
    platforms.push_back(Platform(sf::Vector2f(400.f, 300.f), sf::Vector2f(150.f, 20.f), sf::Color::Yellow));  // green
}



void Game::run() {
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        processEvents();
        player.handleInput();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}


void Game::update(float dt) {
    player.update(dt, platforms);

    std::ifstream file("command.txt");
    std::string command;
    if (file >> command) {
        if (command == "jump") {
            player.voiceJump();  // You’ll write this function
        }
        if (command == "left") {
            player.voiceMove(-1);  // move left
        }
        if (command == "right") {
            player.voiceMove(1);   // move right
        }

        // Clear the file after use
        std::ofstream clear("command.txt", std::ios::trunc);
    }
}


void Game::render() {
    window.clear();
    player.draw(window);
    for (auto& platform : platforms)
        platform.draw(window);
    window.display();
}
