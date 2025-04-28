#include "kolo.hpp"

Kolo::Kolo(float radius, float x, float y, const sf::Color &color, float movementSpeed) : speed(movementSpeed), velocity(0, 0), isJumping(false), groundLevel(y)
{
    shape.setRadius(radius);
    shape.setPosition({x, y});
    shape.setFillColor(color);
    shape.setOrigin({radius, radius});
}

void Kolo::handleInput()
{
    float moveX = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        moveX = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        moveX = 1;
    }
    velocity.x = moveX * 10.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !isJumping)
    {
        jump();
    }
}

void Kolo::update(float deltaTime)
{
    velocity.y += gravity * 10 * deltaTime;
    shape.move(velocity * speed * deltaTime);
    if (shape.getPosition().y >= groundLevel)
    {
        shape.setPosition({shape.getPosition().x, groundLevel});
        velocity.y = 0;
        isJumping = false;
    }
}

void Kolo::jump()
{
    velocity.y = jumpForce * 5;
    isJumping = true;
}

void Kolo::draw(sf::RenderWindow &window) const
{
    window.draw(shape);
}

const sf::CircleShape &Kolo::getShape() const
{
    return shape;
}
