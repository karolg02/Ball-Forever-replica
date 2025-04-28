#include <iostream>
#include <SFML/Graphics.hpp>
#include "features/kolo.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test");
    window.setFramerateLimit(144);
    sf::Clock clock;

    const float radius = 30.f;
    const float groundY = 500.f;
    Kolo kolo(radius, 400.f, groundY - radius, sf::Color::Red, 5.f);

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

        window.clear(sf::Color::Black);

        sf::RectangleShape ground(sf::Vector2f(800.f, 100.f));
        ground.setPosition({0.f, groundY});
        ground.setFillColor(sf::Color::Green);
        window.draw(ground);

        kolo.draw(window);
        window.display();
    }

    return 0;
}