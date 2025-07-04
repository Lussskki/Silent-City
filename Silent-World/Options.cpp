#include "Options.hpp"

bool Options::fullscreen = false;

Options::Options(sf::RenderWindow& windowRef) {
    window = &windowRef;

    font.loadFromFile("arial.ttf");

    backgroundTexture.loadFromFile("options-jimi-hendrix.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window->getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window->getSize().y) / backgroundTexture.getSize().y
    );

    updateItems();
}

void Options::updateItems() {
    items.clear();
    std::vector<std::string> texts = {
        "Music Volume: " + std::to_string(musicVolume),
        std::string("Fullscreen: ") + (fullscreen ? "On" : "Off"),
        "Back"
    };

    for (int i = 0; i < texts.size(); ++i) {
        sf::Text text(texts[i], font, 30);
        text.setPosition(100.f, 150.f + i * 60.f);
        text.setFillColor(i == selectedIndex ? selectedColor : normalColor);
        items.push_back(text);
    }
}

int Options::run(sf::RenderWindow& window) {
    while (window.isOpen() && !shouldExit) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return 2;

            // Keyboard input
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up)
                    moveUp();
                else if (event.key.code == sf::Keyboard::Down)
                    moveDown();
                else if (event.key.code == sf::Keyboard::Left && selectedIndex == 0)
                    adjustVolume(-10);
                else if (event.key.code == sf::Keyboard::Right && selectedIndex == 0)
                    adjustVolume(10);
                else if (event.key.code == sf::Keyboard::Enter)
                    toggleOption();
                else if (event.key.code == sf::Keyboard::Escape)
                    return 1;
            }

            // Mouse hover
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                for (int i = 0; i < items.size(); ++i) {
                    if (items[i].getGlobalBounds().contains(mousePos)) {
                        selectedIndex = i;
                        break;
                    }
                }
            }

            // Mouse click
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (items[selectedIndex].getGlobalBounds().contains(mousePos)) {
                    toggleOption();
                }
            }
        }

        // Hover color update
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        for (int i = 0; i < items.size(); ++i) {
            if (i == selectedIndex || items[i].getGlobalBounds().contains(mousePos))
                items[i].setFillColor(selectedColor);
            else
                items[i].setFillColor(normalColor);
        }

        draw(window);
    }

    return 1;
}

void Options::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(backgroundSprite);
    for (const auto& item : items)
        window.draw(item);
    window.display();
}

void Options::moveUp() {
    if (selectedIndex > 0) {
        selectedIndex--;
        updateItems();
    }
}

void Options::moveDown() {
    if (selectedIndex < items.size() - 1) {
        selectedIndex++;
        updateItems();
    }
}

void Options::adjustVolume(int delta) {
    musicVolume += delta;
    if (musicVolume > 100) musicVolume = 100;
    if (musicVolume < 0) musicVolume = 0;
    updateItems();
}

void Options::toggleOption() {
    if (selectedIndex == 1) { // Toggle fullscreen
        fullscreen = !fullscreen;

        sf::Vector2u texSize = backgroundTexture.getSize();

        window->close();
        if (fullscreen) {
            window->create(sf::VideoMode::getDesktopMode(), "Silent City", sf::Style::Fullscreen);
        }
        else {
            window->create(sf::VideoMode(800, 600), "Silent City", sf::Style::Close);
        }

        backgroundSprite.setScale(
            static_cast<float>(window->getSize().x) / texSize.x,
            static_cast<float>(window->getSize().y) / texSize.y
        );
    }
    else if (selectedIndex == 2) {
        shouldExit = true;
    }

    updateItems();
}
