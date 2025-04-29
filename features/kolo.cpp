#include "kolo.hpp"
#include <iostream>
#include <algorithm>

Kolo::Kolo(float radius, float x, float y, const sf::Color &color, float movementSpeed)
    : speed(movementSpeed),
      velocity(0.f, 0.f),
      isJumping(false),
      isCharging(false),
      chargeTime(0.f),
      haveCollision(false),
      wasSpacePressedLastFrame(false)
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

    velocity.x = 50 * moveX * speed; // Użyj zmiennej speed zamiast stałej wartości 500.f

    bool spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

    // Skok możliwy tylko gdy jest kolizja (na ziemi) i nie jesteśmy w trakcie skoku
    if (spacePressed && !wasSpacePressedLastFrame && haveCollision && !isJumping)
    {
        // Rozpoczęcie ładowania
        startCharging();
    }

    if (!spacePressed && wasSpacePressedLastFrame && isCharging && haveCollision)
    {
        // Puszczenie spacji = skok
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
    if (isCharging)
    {
        chargeTime += deltaTime;                // Ładuj siłę skoku
        chargeTime = std::min(chargeTime, 1.f); // Ogranicz do maksimum (np. 1 sekunda)
        shape.setFillColor(sf::Color::Yellow);  // Efekt wizualny ładowania (opcjonalnie)
    }

    if (!haveCollision)
    {
        velocity.y += gravity * deltaTime;
    }
    else
    {
        velocity.y = 0;
        isJumping = false;
    }

    shape.move(velocity * deltaTime);
}

void Kolo::jump()
{
    isJumping = true;
    isCharging = false;

    float force = minJumpForce + (maxJumpForce - minJumpForce) * std::min(chargeTime, 1.f);
    velocity.y = force; // Poprawka: skok w górę = ujemna prędkość

    haveCollision = false;
    chargeTime = 0.f;
    shape.setFillColor(sf::Color::Red); // Wskazanie skoku
}

void Kolo::checkCollision(const sf::RectangleShape &block)
{
    const auto koloBounds = shape.getGlobalBounds();
    const auto blockBounds = block.getGlobalBounds();

    if (!koloBounds.findIntersection(blockBounds))
    {
        return; // Brak kolizji
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
        // Kolizja pionowa
        if (fromTop < fromBottom)
        {
            // Lądowanie
            shape.move({0.f, -fromTop});
            velocity.y = 0.f;
            haveCollision = true; // Ustawiamy flagę kolizji
            isJumping = false;
        }
        else
        {
            // Uderzenie od dołu
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
