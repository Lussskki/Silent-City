#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

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

    std::vector<sf::Text> items;
    sf::Font font;
    int selectedIndex = 0;

    // Background image
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    bool shouldExit = false;
   
    int musicVolume = 50;

    sf::Color selectedColor = sf::Color(120, 220, 120); // Acid Green
    sf::Color normalColor = sf::Color(185, 100, 210);   // Psychedelic Plum
    sf::RenderWindow* window;  // pointer to main window

    void updateItems();
};
