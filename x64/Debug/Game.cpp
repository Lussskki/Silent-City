#include "Game.hpp"
#include <fstream>
#include <string>

Game::Game(sf::RenderWindow& win)
    : window(win)
{
    // Platforms
    platforms.push_back(Platform({ 170.f, 550.f }, { 100.f, 20.f }, sf::Color::Red));
    platforms.push_back(Platform({ 600.f, 550.f }, { 200.f, 20.f }, sf::Color::Blue));
    platforms.push_back(Platform({ 400.f, 500.f }, { 150.f, 20.f }, sf::Color::Yellow));

    platforms.push_back(Platform({ 170.f, 450.f }, { 100.f, 20.f }, sf::Color::Magenta));
    platforms.push_back(Platform({ 600.f, 450.f }, { 200.f, 20.f }, sf::Color::Blue));
    platforms.push_back(Platform({ 400.f, 400.f }, { 150.f, 20.f }, sf::Color::Yellow));

    platforms.push_back(Platform({ 170.f, 350.f }, { 100.f, 20.f }, sf::Color::Magenta));
    platforms.push_back(Platform({ 600.f, 350.f }, { 200.f, 20.f }, sf::Color::Blue));
    platforms.push_back(Platform({ 400.f, 300.f }, { 150.f, 20.f }, sf::Color::Yellow));

    // Load font
    font.loadFromFile("arial.ttf");

    // Setup return to menu text
    returnText.setFont(font);
    returnText.setString("Return to Menu");
    returnText.setCharacterSize(24);
    returnText.setFillColor(sf::Color::White);
    returnText.setPosition(10.f, 10.f);  // top-left corner

    updateView(); // Set up the initial view
}

bool Game::run() {
    isRunning = true; 

    while (window.isOpen() && isRunning) {
        float dt = clock.restart().asSeconds();
        processEvents();
        player.handleInput();
        update(dt);
        render();

    }

    return isRunning == false;
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                isRunning = false;  // Exit game loop, return to menu
            }
        }
        else if (event.type == sf::Event::Resized) {
            updateView();
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (returnText.getGlobalBounds().contains(mousePos)) {
                    isRunning = false;
                }
            }
        }
    }
}

void Game::update(float dt) {
    player.update(dt, platforms);

    // Hover effect for returnText
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (returnText.getGlobalBounds().contains(mousePos)) {
        returnText.setFillColor(sf::Color::Yellow);
    }
    else {
        returnText.setFillColor(sf::Color::White);
    }

    // Voice command processing
    std::ifstream file("command.txt");
    std::string command;
    if (file >> command) {
        if (command == "jump") player.voiceJump();
        else if (command == "left") player.voiceMove(-1);
        else if (command == "right") player.voiceMove(1);
        std::ofstream clear("command.txt", std::ios::trunc); // Clear file
    }
}

void Game::render() {
    window.clear();
    window.setView(view);

    player.draw(window);

    for (auto& platform : platforms)
        platform.draw(window);

    window.draw(returnText); // Draw the return button

    window.display();
}

void Game::updateView() {
    float virtualWidth = 800.f;
    float virtualHeight = 600.f;

    view.setSize(virtualWidth, virtualHeight);
    view.setCenter(virtualWidth / 2.f, virtualHeight / 2.f);

    sf::Vector2u screenSize = window.getSize();
    float windowRatio = static_cast<float>(screenSize.x) / screenSize.y;
    float viewRatio = virtualWidth / virtualHeight;

    float viewportWidth = 1.f;
    float viewportHeight = 1.f;
    float viewportX = 0.f;
    float viewportY = 0.f;

    if (windowRatio > viewRatio) {
        // Window is wider than view: add black bars left/right
        viewportWidth = viewRatio / windowRatio;
        viewportX = (1.f - viewportWidth) / 2.f;
    }
    else if (windowRatio < viewRatio) {
        // Window is taller than view: add black bars top/bottom
        viewportHeight = windowRatio / viewRatio;
        viewportY = (1.f - viewportHeight) / 2.f;
    }

    view.setViewport(sf::FloatRect(viewportX, viewportY, viewportWidth, viewportHeight));
    window.setView(view);
}
