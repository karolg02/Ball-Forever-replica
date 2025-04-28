#include "kolo.hpp"
// #include <iostream>
Kolo::Kolo(float radius, float x, float y, const sf::Color &color, float movementSpeed)
    : speed(movementSpeed),
      velocity(0.f, 0.f),
      isJumping(false),
      isCharging(false),
      chargeTime(0.f),
      groundLevel(y + radius)
{
    shape.setRadius(radius);
    shape.setOrigin({radius, radius});
    shape.setPosition({x, y});
    shape.setFillColor(color);
}

void Kolo::handleInput()
{
    float moveX = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        moveX = -1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        moveX = 1.f;

    velocity.x = moveX * 100.f;

    bool spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

    if (spacePressed && !wasSpacePressedLastFrame && !isJumping)
    {
        startCharging();
    }
    else if (!spacePressed && wasSpacePressedLastFrame && isCharging)
    {
        jump();
    }

    wasSpacePressedLastFrame = spacePressed;
}

void Kolo::startCharging()
{
    isCharging = true;
    chargeTime = 0.f;
}

void Kolo::update(float deltaTime)
{
    if (isCharging && !isJumping)
    {
        chargeTime += deltaTime * chargeSpeed;
        int colorOffset = static_cast<int>(chargeTime * 150);
        colorOffset = std::min(colorOffset, 255);
        shape.setFillColor(sf::Color(255, 255 - colorOffset, 255 - colorOffset));
    }

    velocity.y += gravity * deltaTime;
    shape.move(velocity * deltaTime);

    float radius = shape.getRadius();
    float posY = shape.getPosition().y;

    if (posY + radius >= groundLevel)
    {
        shape.setPosition({shape.getPosition().x, groundLevel - radius});
        velocity.y = 0.f;

        isJumping = false;

        if (!isCharging)
        {
            chargeTime = 0.f;
            shape.setFillColor(sf::Color::Red);
        }
    }
}

void Kolo::jump()
{
    isJumping = true;
    isCharging = false;

    float force = minJumpForce + (maxJumpForce - minJumpForce) * std::min(chargeTime, 1.f);
    velocity.y = force;

    chargeTime = 0.f;
}

void Kolo::draw(sf::RenderWindow &window) const
{
    window.draw(shape);
}

const sf::CircleShape &Kolo::getShape() const
{
    return shape;
}
