#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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

    sf::Sound kickSound, snareSound , hihatSound;
    kickSound.setBuffer(kickBuffer);
    snareSound.setBuffer(snareBuffer);
    hihatSound.setBuffer(hihatBuffer);

    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color(0, 200, 0));
    circle.setPosition(200, 200);

    while (App.isOpen())
    {
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed) {
                App.close();
            } else if (Event.type == sf::Event::JoystickButtonPressed) {
                std::cout << "JoystickButtonEvent: " << Event.joystickButton.button << std::endl;

                switch (Event.joystickButton.button) {
                case 0:
                    kickSound.play();
                    break;

                case 1:
                    snareSound.play();
                    break;

                case 4:
                    hihatSound.play();
                    break;

                default: {}
                }
            }
        }

        App.clear(sf::Color(0, 0, 0));
        App.draw(circle);
        App.display();
    }
 
    return 0;
}
