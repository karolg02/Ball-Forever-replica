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
    const float groundLevel;
    const float minJumpForce = -400.f;
    const float maxJumpForce = -800.f;
    const float chargeSpeed = 1.5f;
    bool wasSpacePressedLastFrame = false;

public:
    Kolo(float radius, float x, float y, const sf::Color &color, float movementSpeed);

    void update(float deltaTime);
    void draw(sf::RenderWindow &window) const;
    void handleInput();
    void startCharging();
    void jump();

    const sf::CircleShape &getShape() const;
};
