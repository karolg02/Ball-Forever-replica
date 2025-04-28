#pragma once
#include <SFML/Graphics.hpp>

class Kolo
{
private:
    sf::CircleShape shape;
    float speed;
    sf::Vector2f velocity;
    bool isJumping;
    const float gravity = 9.8f;
    const float jumpForce = -15.0f;
    const float groundLevel;

public:
    Kolo(float radius, float x, float y, const sf::Color &color, float movementSpeed);

    void update(float deltaTime);
    void draw(sf::RenderWindow &window) const;
    void handleInput();
    void jump();

    const sf::CircleShape &getShape() const;
};