#include <istream>
#include <ostream>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "./player.hpp"
#include "./lineartransition.hpp"

sf::Color operator-(const sf::Color &c1, const sf::Color &c2)
{
    return sf::Color(c1.r - c2.r, 
                     c1.g - c2.g, 
                     c1.b - c2.b, 
                     c1.a - c2.a);
}

sf::Color operator*(const sf::Color &color, float f)
{
    return sf::Color(color.r * f,
                     color.g * f,
                     color.b * f);
}

sf::CircleShape playerToCircle(const Player &player)
{
    const float radius = player.radius.value();
    sf::CircleShape circle(player.radius.value());
    circle.setFillColor(player.color.value());
    circle.setPosition(player.position.value() - sf::Vector2f(radius, radius));
    return circle;
}

int main()
{
    sf::RenderWindow App(sf::VideoMode(1024, 768, 32), "Hello World - SFML");
    sf::SoundBuffer kickBuffer, snareBuffer, hihatBuffer;

    if (!kickBuffer.loadFromFile("data/kick.wav")) {
        std::cout << "[ERROR] Cannot load data/kick.wav" << std::endl;
        return 1;
    }

    if (!snareBuffer.loadFromFile("data/snare.wav")) {
        std::cout << "[ERROR] Cannot load data/snare.wav" << std::endl;
         return 1;
    }

    if (!hihatBuffer.loadFromFile("data/hihat.wav")) {
        std::cout << "[ERROR] Cannot load data/hihat.wav" << std::endl;
        return 1;
    }

    Player player(sf::Vector2<float>(200.0f, 200.0f),
                  50.0f,
                  sf::Color(255.0f, 255.0f, 255.0f));

    sf::Sound kickSound, snareSound , hihatSound;
    kickSound.setBuffer(kickBuffer);
    snareSound.setBuffer(snareBuffer);
    hihatSound.setBuffer(hihatBuffer);

    sf::Clock clock;

    const sf::Int32 moveTime = 150;
    const sf::Int32 colorTime = 700;

    while (App.isOpen())
    {
        // std::cout << state << std::endl;
        clock.restart();
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed) {
                App.close();
            } else if (Event.type == sf::Event::KeyPressed) {
                switch (Event.key.code) {
                case sf::Keyboard::Space:         // kick
                    player.radius.animate(moveTo(70.0f, colorTime, 50.0f));
                    player.color.animate(moveTo(sf::Color::Red, colorTime, sf::Color::White));
                    player.position.animate(moveBy(player.position.value(), 
                                                   moveTime, 
                                                   sf::Vector2f(100.0f, 0.0f)));

                    kickSound.play();
                    break;

                case sf::Keyboard::S:         // snare
                    player.radius.animate(moveTo(70.0f, colorTime, 50.0f));
                    player.color.animate(moveTo(sf::Color::Green, colorTime, sf::Color::White));
                    player.position.animate(moveBy(player.position.value(), 
                                                   moveTime, 
                                                   sf::Vector2f(0.0f, 100.0f)));

                    snareSound.play();
                    break;

                case sf::Keyboard::P:         // hihat
                    player.radius.animate(moveTo(70.0f, colorTime, 50.0f));
                    player.color.animate(moveTo(sf::Color::Blue, colorTime, sf::Color::White));
                    player.position.animate(moveBy(player.position.value(), 
                                                   moveTime, 
                                                   sf::Vector2f(0.0f, -100.0f)));
                    hihatSound.play();
                    break;

                default: {}
                }
            }
        }

        App.clear(sf::Color(0, 0, 0));
        player.tick(clock.getElapsedTime().asMilliseconds());
        App.draw(playerToCircle(player));
        App.display();
    }
 
    return 0;
}
