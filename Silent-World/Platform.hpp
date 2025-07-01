#pragma once
#include <SFML/Graphics.hpp>

class Platform {
public:
    Platform(sf::Vector2f pos, sf::Vector2f size, sf::Color color);
    void draw(sf::RenderWindow& window);
    const sf::RectangleShape& getShape() const; // <-- Add this

private:
    sf::RectangleShape shape;
};
