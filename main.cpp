#include <istream>
#include <ostream>
#include <iostream>
#include <vector>
#include <deque>
#include <tuple>
#include <string>
#include <fstream>
#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "./tunnel.hpp"
#include "./captures.hpp"
#include "./player.hpp"
#include "./lineartransition.hpp"
#include "./lineartransitionbuilder.hpp"
#include "./seqcombinator.hpp"

const sf::Color WALL_COLOR = sf::Color(0, 130, 140);

const sf::Int32 SCREEN_WIDTH = 1280;
const sf::Int32 SCREEN_HEIGHT = 720;

const sf::Int32 MOVE_TIME = 500;
const sf::Int32 COLOR_TIME = 700;

const sf::Vector2f PLAYER_INIT_POSITION(200.0f, 200.0f);
const float PLAYER_INIT_RADIUS = 50.0f;
const sf::Color PLAYER_INIT_COLOR = sf::Color::White;
const float PLAYER_MOVE_DISTANCE = 250.0f;

sf::Color operator*(const sf::Color &color, float f)
{
    return sf::Color(color.r * f,
                     color.g * f,
                     color.b * f);
}

sf::CircleShape playerToCircle(const Player &player)
{
    const float radius = player.radius.value();
    sf::CircleShape circle(radius);
    circle.setFillColor(player.color.value());
    circle.setPosition(SCREEN_WIDTH / 2.0f - radius,
                       SCREEN_HEIGHT / 2.0f - radius);
    // circle.setPosition(player.position.value() - sf::Vector2f(radius, radius));
    return circle;
}

void stepPlayer(Player &player, 
                const sf::Color &flashColor, 
                const sf::Vector2f direction,
                sf::Sound &sound)
{
    player.color.animate(from(flashColor)
                         .to(sf::Color::White)
                         .during(COLOR_TIME));
    player.position.animate(from(player.position.value())
                            .by(direction)
                            .during(MOVE_TIME));
    sound.play();
}

int main()
{
    sf::RenderWindow App(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Hello World - SFML");
    sf::SoundBuffer kickBuffer, snareBuffer, hihatBuffer, shamanBuffer;

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

    if (!shamanBuffer.loadFromFile("data/shaman.wav")) {
        std::cout << "[ERROR] Cannot load data/shaman.wav" << std::endl;
        return 1;
    }

    Player player(sf::Vector2f(200.0f, 200.0f),
                  50.0f,
                  sf::Color::White);

    Tunnel tunnel;
    digTunnel("tunnel.txt", tunnel);

    sf::Sound kickSound, snareSound, hihatSound, shamanSound;
    kickSound.setBuffer(kickBuffer);
    snareSound.setBuffer(snareBuffer);
    hihatSound.setBuffer(hihatBuffer);
    shamanSound.setBuffer(shamanBuffer);

    sf::Clock clock;
    sf::Clock playClock;

    std::deque<std::pair<int, sf::Int32>> captures;
    // loadCaptureInfo(captures, "replay.txt");

    sf::Int32 currentTime = 0;

    while (App.isOpen())
    {
        // std::cout << state << std::endl;
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed) {
                App.close();
            } else if (Event.type == sf::Event::KeyPressed) {
                switch (Event.key.code) {
                case sf::Keyboard::Space:         // kick
                    // captures.push_back(std::make_pair(0, playClock.restart().asMilliseconds()));
                    stepPlayer(player, sf::Color::Red, sf::Vector2f(PLAYER_MOVE_DISTANCE, 0.0f), kickSound);
                    break;

                case sf::Keyboard::S:         // snare
                    // captures.push_back(std::make_pair(1, playClock.restart().asMilliseconds()));
                    stepPlayer(player, sf::Color::Green, sf::Vector2f(0.0f, PLAYER_MOVE_DISTANCE), snareSound);
                    break;

                case sf::Keyboard::P:         // hihat
                    stepPlayer(player, sf::Color::Blue, sf::Vector2f(0.0f, -PLAYER_MOVE_DISTANCE), hihatSound);
                    break;

                case sf::Keyboard::H: // shaman
                    stepPlayer(player, sf::Color::Yellow, sf::Vector2f(-PLAYER_MOVE_DISTANCE, 0.0f), shamanSound);
                    break;

                case sf::Keyboard::G:
                    digTunnel("tunnel.txt", tunnel);
                    player.position.animate(from(player.position.value()).to(PLAYER_INIT_POSITION).during(MOVE_TIME));
                    player.color.animate(from(player.color.value()).to(PLAYER_INIT_COLOR).during(MOVE_TIME));
                    player.radius.animate(from(player.radius.value()).to(PLAYER_INIT_RADIUS).during(MOVE_TIME));
                    break;

                case sf::Keyboard::Q:
                    dumpCaptureInfo(captures, "captures.txt");
                    break;

                default: {}
                }
            }
        }

        sf::Int32 deltaTime = clock.restart().asMilliseconds();
        currentTime += deltaTime;
        
        // if (!captures.empty()) {
        //     auto capture = captures.front();
        //     if (capture.second <= currentTime) {
        //         switch (capture.first) {
        //         case 0:
        //             stepPlayer(player, sf::Color::Red, sf::Vector2f(PLAYER_MOVE_DISTANCE, 0.0f), kickSound);
        //             break;

        //         case 1:
        //             stepPlayer(player, sf::Color::Green, sf::Vector2f(0.0f, PLAYER_MOVE_DISTANCE), snareSound);
        //             break;

        //         default: {}
        //         }

        //         currentTime = 0;
        //         captures.pop_front();
        //     }
        // }

        App.clear(WALL_COLOR);
        player.tick(deltaTime);

        for (const auto &rect: tunnel) {
            sf::RectangleShape shape;
            shape.setPosition(rect.left - player.position.value().x + SCREEN_WIDTH / 2.0f, 
                              rect.top - player.position.value().y + SCREEN_HEIGHT / 2.0f);
            shape.setSize(sf::Vector2f(rect.width, rect.height));
            shape.setFillColor(sf::Color::Black);
            App.draw(shape);
        }

        App.draw(playerToCircle(player));
        App.display();
    }
 
    return 0;
}
