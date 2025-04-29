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

    velocity.x = moveX * 500.f;

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

void Kolo::checkCollision(const sf::RectangleShape &block)
{
    const auto koloBounds = shape.getGlobalBounds();
    const auto blockBounds = block.getGlobalBounds();

    if (!(koloBounds.position.x < blockBounds.position.x + blockBounds.size.x &&
          koloBounds.position.x + koloBounds.size.x > blockBounds.position.x &&
          koloBounds.position.y < blockBounds.position.y + blockBounds.size.y &&
          koloBounds.position.y + koloBounds.size.y > blockBounds.position.y))
    {
        return; // brak kolizji
    }

    float koloBottom = koloBounds.position.y + koloBounds.size.y;
    float koloRight = koloBounds.position.x + koloBounds.size.x;
    float blockBottom = blockBounds.position.y + blockBounds.size.y;
    float blockRight = blockBounds.position.x + blockBounds.size.x;

    float fromLeft = std::abs(koloRight - blockBounds.position.x);
    float fromRight = std::abs(blockRight - koloBounds.position.x);
    float fromTop = std::abs(koloBottom - blockBounds.position.y);
    float fromBottom = std::abs(blockBottom - koloBounds.position.y);

    float minX = std::min(fromLeft, fromRight);
    float minY = std::min(fromTop, fromBottom);

    if (minX < minY)
    {
        // Kolizja pozioma
        if (fromLeft < fromRight)
            shape.move({-fromLeft, 0.f});
        else
            shape.move({fromRight, 0.f});
        velocity.x = 0.f;
    }
    else
    {
        // Kolizja pionowa
        if (fromTop < fromBottom)
        {
            shape.move({0.f, -fromTop});
            velocity.y = 0.f;
            isJumping = false;
            isCharging = false;
            chargeTime = 0.f;
            shape.setFillColor(sf::Color::Red);
        }
        else
        {
            shape.move({0.f, fromBottom});
            velocity.y = 0.f;
        }
    }
}

void Kolo::draw(sf::RenderWindow &window) const
{
    window.draw(shape);
}

const sf::CircleShape &Kolo::getShape() const
{
    return shape;
}
