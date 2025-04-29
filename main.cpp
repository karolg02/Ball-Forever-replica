#include <iostream>
#include <SFML/Graphics.hpp>
#include "features/kolo.hpp"

int main()
{
    unsigned int static windowX = 1200;
    unsigned int static windowY = 800;
    sf::RenderWindow window(sf::VideoMode({windowX, windowY}), "Test");
    window.setFramerateLimit(144);
    sf::Clock clock;

    const float radius = 30.f;
    const float groundY = windowY;
    Kolo kolo(radius, 400.f, groundY - radius, sf::Color::Red, 5.f);

    sf::RectangleShape block(sf::Vector2f(100.f, -50.f));
    block.setFillColor(sf::Color::Green);
    block.setPosition({500.f, groundY});

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        kolo.handleInput();
        kolo.update(deltaTime);
        kolo.checkCollision(block);

        window.clear(sf::Color::Black);

        sf::RectangleShape ground(sf::Vector2f(800.f, 0.f));
        ground.setPosition({0.f, groundY});
        window.draw(ground);

        window.draw(block);

        kolo.draw(window);
        window.display();
    }

    return 0;
}