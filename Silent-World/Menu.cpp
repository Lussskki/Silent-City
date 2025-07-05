#include "Menu.hpp"
#include "Options.hpp"

Menu::Menu(sf::RenderWindow& window) {
    font.loadFromFile("arial.ttf");
    std::vector<std::string> texts = { "Play", "Options", "Exit" };

    backgroundTexture.loadFromFile("menu-jimi-hendrix.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(800.f / backgroundTexture.getSize().x, 600.f / backgroundTexture.getSize().y);

    sf::Vector2u winSize = window.getSize();
    float spacing = 50.f;
    float totalHeight = texts.size() * spacing;
    float startY = winSize.y - totalHeight - 50.f;

    for (int i = 0; i < texts.size(); ++i) {
        sf::Text text(texts[i], font, 36);
        text.setPosition(50.f, startY + i * spacing);
        text.setFillColor(normalColor);
        options.push_back(text);
    }

    options[selectedIndex].setFillColor(selectedColor);
}

int Menu::run(sf::RenderWindow& window) {
    refresh(window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return 2;  // Exit code

            // Mouse hover
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                for (size_t i = 0; i < options.size(); ++i) {
                    if (options[i].getGlobalBounds().contains(mousePos)) {
                        options[selectedIndex].setFillColor(normalColor);
                        selectedIndex = static_cast<int>(i);
                        options[selectedIndex].setFillColor(selectedColor);
                        break;
                    }
                }
            }

            // Mouse click
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (options[selectedIndex].getGlobalBounds().contains(mousePos)) {
                    if (selectedIndex == 0) return 0; // Play
                    if (selectedIndex == 1) {
                        Options optionsMenu(window);
                        optionsMenu.run(window);

                        // Recreate window after fullscreen toggle
                        window.close();
                        if (Options::fullscreen)
                            window.create(sf::VideoMode::getDesktopMode(), "Silent World", sf::Style::Fullscreen);
                        else
                            window.create(sf::VideoMode(800, 600), "Silent World", sf::Style::Close);

                        // Return 1 to indicate we need to recreate the menu
                        return 1;
                    }
                    if (selectedIndex == 2) return 2; // Exit
                }
            }

            // Keyboard input
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) moveUp();
                else if (event.key.code == sf::Keyboard::Down) moveDown();
                else if (event.key.code == sf::Keyboard::Enter) {
                    if (selectedIndex == 0) return 0;
                    else if (selectedIndex == 1) {
                        Options optionsMenu(window);
                        optionsMenu.run(window);

                        // Recreate window after fullscreen toggle
                        window.close();
                        if (Options::fullscreen)
                            window.create(sf::VideoMode::getDesktopMode(), "Silent World", sf::Style::Fullscreen);
                        else
                            window.create(sf::VideoMode(800, 600), "Silent World", sf::Style::Close);

                        return 1;
                    }
                    else if (selectedIndex == 2) return 2;
                }
            }
        }

        draw(window);
    }

    return 2;
}

void Menu::draw(sf::RenderWindow& window) {
    window.setView(window.getDefaultView());
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

void Menu::refresh(sf::RenderWindow& window) {
    window.setView(window.getDefaultView());

    backgroundTexture.loadFromFile("menu-jimi-hendrix.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    float spacing = 50.f;
    float totalHeight = options.size() * spacing;
    float startY = window.getSize().y - totalHeight - 50.f;

    for (size_t i = 0; i < options.size(); ++i) {
        sf::Text& text = options[i];
        float x = 50.f;
        float y = startY + i * spacing;
        text.setPosition(x, y);
    }
}
