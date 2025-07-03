#include "Menu.hpp"

Menu::Menu(float width, float height) {
    font.loadFromFile("arial.ttf");
    std::vector<std::string> texts = { "Play", "Options", "Exit" };

    for (int i = 0; i < texts.size(); ++i) {
        sf::Text text(texts[i], font, 36);
        text.setPosition(width / 2.f - 50, height / 2.f + i * 60 - 60);
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        options.push_back(text);
    }
}

int Menu::run(sf::RenderWindow& window) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return 2; // Exit selected

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up)
                    moveUp();
                else if (event.key.code == sf::Keyboard::Down)
                    moveDown();
                else if (event.key.code == sf::Keyboard::Enter)
                    return selectedIndex;
            }
        }
        draw(window);
    }
    return 2;
}

void Menu::draw(sf::RenderWindow& window) {
    window.clear();
    for (const auto& text : options)
        window.draw(text);
    window.display();
}

void Menu::moveUp() {
    if (selectedIndex > 0) {
        options[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex--;
        options[selectedIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedIndex < options.size() - 1) {
        options[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex++;
        options[selectedIndex].setFillColor(sf::Color::Red);
    }
}
