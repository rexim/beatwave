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
    sf::CircleShape circle(player.radius.value());
    circle.setFillColor(player.color.value());
    circle.setPosition(player.position.value());
    return circle;
}

int main()
{
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Hello World - SFML");
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

    while (App.isOpen())
    {
        // std::cout << state << std::endl;
        clock.restart();
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed) {
                App.close();
            } else if (Event.type == sf::Event::JoystickButtonPressed) {
                switch (Event.joystickButton.button) {
                case 0:         // kick
                    player.radius.animate(moveTo(70.0f, 300, 50.0f));
                    player.color.animate(moveTo(sf::Color::Red, 300, sf::Color::White));
                    player.position.animate(moveBy(player.position.value(), 
                                                   300, 
                                                   sf::Vector2f(100.0f, 0.0f)));

                    kickSound.play();
                    break;

                case 1:         // snare
                    player.color.animate(moveTo(sf::Color::Green, 300, sf::Color::White));
                    snareSound.play();
                    break;

                case 2:         // hihat
                    player.radius.animate(moveTo(70.0f, 300, 50.0f));
                    player.color.animate(moveTo(sf::Color::Blue, 300, sf::Color::White));
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
