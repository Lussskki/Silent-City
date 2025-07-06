#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Options {
public:
    static bool fullscreen;

    Options(sf::RenderWindow& window);
    int run(sf::RenderWindow& window); // returns when "Back" is selected

private:
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    void toggleOption();
    void adjustVolume(int delta);
    void updateItems();

    std::vector<sf::Text> items;
    sf::Font font;
    int selectedIndex = 0;

    // Background image
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    bool shouldExit = false;
    bool isEnglish;

    std::string language;      // single declaration here, private

    int musicVolume = 50;

    sf::Color selectedColor = sf::Color(120, 220, 120); // Acid Green
    sf::Color normalColor = sf::Color(185, 100, 210);   // Psychedelic Plum

    sf::RenderWindow* window;  // pointer to main window
};
