#pragma once
#include <SFML/Graphics.hpp>

class Kolo
{
private:
    sf::CircleShape shape;
    float speed;
    sf::Vector2f velocity;
    bool isJumping;
    bool isCharging;
    float chargeTime;
    const float gravity = 980.f;
    const float minJumpForce = -500.f;
    const float maxJumpForce = -1000.f;
    const float chargeSpeed = 1.5f;
    bool wasSpacePressedLastFrame;
    bool haveCollision;

public:
    Kolo(float radius, float x, float y, const sf::Color &color, float movementSpeed);

    void update(float deltaTime);
    void draw(sf::RenderWindow &window) const;
    void handleInput();
    void startCharging();
    void jump();
    void checkCollision(const sf::RectangleShape &block);

    const sf::CircleShape &getShape() const;
};
