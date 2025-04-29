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
    Kolo kolo(radius, 400.f, 400.f, sf::Color::Red, 5.f);

    sf::RectangleShape block(sf::Vector2f(100.f, -50.f));
    block.setFillColor(sf::Color::Green);
    block.setPosition({500.f, groundY - 100});

    sf::RectangleShape ground(sf::Vector2f(800.f, 50.f)); // Ustawiamy wysokość na 50 pikseli
    ground.setPosition({0.f, groundY - 50.f});            // Ustawiamy na dole okna

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

        kolo.checkCollision(ground);
        kolo.checkCollision(block);
        kolo.handleInput();
        kolo.update(deltaTime);

        window.clear(sf::Color::Black);

        window.draw(ground);

        window.draw(block);

        kolo.draw(window);
        window.display();
    }

    return 0;
}