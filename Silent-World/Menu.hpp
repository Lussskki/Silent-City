#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Menu {
public:
    Menu(float width, float height);
    int run(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedIndex() const;

private:
    std::vector<sf::Text> options;
    int selectedIndex = 0;
    sf::Font font;
};
