#include "Menu.hpp"
#include "Options.hpp"

Menu::Menu(sf::RenderWindow& window) {
    font.loadFromFile("arial.ttf");
    std::vector<std::string> texts = { "Play", "Options", "Exit" };

    backgroundTexture.loadFromFile("menu-jimi-hendrix.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(800.f / backgroundTexture.getSize().x, 600.f / backgroundTexture.getSize().y);

    for (int i = 0; i < texts.size(); ++i) {
        sf::Text text(texts[i], font, 36);
        text.setPosition(50.f, 450.f + i * 50.f);
        text.setFillColor(normalColor);
        options.push_back(text);
    }

    // first selected one
    options[selectedIndex].setFillColor(selectedColor);
}

int Menu::run(sf::RenderWindow& window) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return 2;

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up)
                    moveUp();
                else if (event.key.code == sf::Keyboard::Down)
                    moveDown();
                else if (event.key.code == sf::Keyboard::Enter) {
                    if (selectedIndex == 0) {
                        return 0; // Play
                    }
                    else if (selectedIndex == 1) {
                        // Open Options screen
                        Options optionsMenu(window);
                        optionsMenu.run(window);

                        // Recreate window after fullscreen toggle
                        window.close();
                        if (Options::fullscreen) {
                            window.create(sf::VideoMode::getDesktopMode(), "Silent World", sf::Style::Fullscreen);
                        }
                        else {
                            window.create(sf::VideoMode(800, 600), "Silent World", sf::Style::Close);
                        }

                        // Reload background (needed after recreate)
                        backgroundTexture.loadFromFile("menu-jimi-hendrix.png");
                        backgroundSprite.setTexture(backgroundTexture);
                        backgroundSprite.setScale(
                            static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
                            static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
                        );
                    }
                    else if (selectedIndex == 2) {
                        return 2; // Exit
                    }
                }
            }
        }

        draw(window);
    }

    return 2;
}

void Menu::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(backgroundSprite);
    for (const auto& text : options)
        window.draw(text);
    window.display();
}

void Menu::moveUp() {
    if (selectedIndex > 0) {
        options[selectedIndex].setFillColor(normalColor);
        selectedIndex--;
        options[selectedIndex].setFillColor(selectedColor);
    }
}

void Menu::moveDown() {
    if (selectedIndex < options.size() - 1) {
        options[selectedIndex].setFillColor(normalColor);
        selectedIndex++;
        options[selectedIndex].setFillColor(selectedColor);
    }
}
