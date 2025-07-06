#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.hpp"
#include <vector>

class Player {
public:
    Player();
    void handleInput();
    void update(float dt, const std::vector<Platform>& platforms); // <-- Add platforms
    void draw(sf::RenderWindow& window);
    void voiceJump();
    void voiceMove(int direction); // -1 = left, 1 = right

private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    float gravity = 900.f;
    float jumpPower = -400.f;
    float moveSpeed = 200.f;
    bool onGround = false;


    void checkCollision(const std::vector<Platform>& platforms);
};
