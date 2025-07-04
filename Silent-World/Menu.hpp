#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Menu {
public:
    Menu(sf::RenderWindow&);
    int run(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    /*int getSelectedIndex() const;*/

private:
    std::vector<sf::Text> options;
    int selectedIndex = 0;
    sf::Font font;

    // menu - background photo
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    // menu - color
    sf::Color selectedColor = sf::Color(120, 220, 120);   // Acid Green
    sf::Color normalColor = sf::Color(185, 100, 210);   // Psychedelic Plum

};
