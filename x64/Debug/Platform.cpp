#include "Platform.hpp"

Platform::Platform(sf::Vector2f position, sf::Vector2f size, sf::Color color) {
    shape.setSize(size);
    shape.setFillColor(color); 
    shape.setOrigin(size / 2.f);
    shape.setPosition(position);
}


void Platform::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

const sf::RectangleShape& Platform::getShape() const {
    return shape;
}
