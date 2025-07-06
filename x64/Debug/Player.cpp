#include "Player.hpp"

Player::Player() 
{
    shape.setSize({ 20.f, 20.f });
    shape.setFillColor(sf::Color::Cyan);
    shape.setPosition(500.f, 600.f);
}

void Player::handleInput() 
{
    velocity.x = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        velocity.x -= moveSpeed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        velocity.x += moveSpeed;

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::J) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && onGround) 
    {
        velocity.y = jumpPower;
        onGround = false;
    }
}

void Player::update(float dt, const std::vector<Platform>& platforms) 
{
    velocity.y += gravity * dt;

    // Predict vertical movement
    sf::Vector2f position = shape.getPosition();
    sf::FloatRect playerBounds = shape.getGlobalBounds();
    sf::FloatRect futureBounds = playerBounds;
    futureBounds.top += velocity.y * dt;

    onGround = false;

    for (const auto& platform : platforms) {
        sf::FloatRect platBounds = platform.getShape().getGlobalBounds();

        if (futureBounds.intersects(platBounds)) {
            // Check if landing on top
            if (velocity.y > 0 && playerBounds.top + playerBounds.height <= platBounds.top + 5) {
                velocity.y = 0;
                position.y = platBounds.top - playerBounds.height;
                onGround = true;
            }
        }
    }

    // Apply vertical movement
    position.y += velocity.y * dt;

    // Apply horizontal input
    position.x += velocity.x * dt;

    // Ground check
    float groundY = 600.f;
    if (position.y + shape.getSize().y >= groundY) {
        position.y = groundY - shape.getSize().y;
        velocity.y = 0;
        onGround = true;
    }

    shape.setPosition(position);
}



void Player::checkCollision(const std::vector<Platform>& platforms) {
    sf::FloatRect playerBounds = shape.getGlobalBounds();

    for (const auto& platform : platforms) {
        sf::FloatRect platBounds = platform.getShape().getGlobalBounds();

        if (playerBounds.intersects(platBounds)) {
            float playerBottom = playerBounds.top + playerBounds.height;
            float platformTop = platBounds.top;

            // Make sure player is falling and came from above
            if (velocity.y > 0 && playerBottom - velocity.y * 0.016f <= platformTop) {
                shape.setPosition(shape.getPosition().x, platformTop - playerBounds.height);
                velocity.y = 0;
                onGround = true;
                break;
            }
        }
    }
}

void Player::voiceJump() {
    if (onGround) {
        velocity.y = jumpPower;
        onGround = false;
    }
}

void Player::voiceMove(int direction) {
    velocity.x = moveSpeed * direction;
}


void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
