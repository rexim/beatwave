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

#include "tunnel.hpp"
#include "captures.hpp"
#include "player.hpp"
#include "lineartransition.hpp"
#include "lineartransitionbuilder.hpp"
#include "seqcombinator.hpp"
#include "util.hpp"
#include "game.hpp"

const sf::Int32 SCREEN_WIDTH = 1280;
const sf::Int32 SCREEN_HEIGHT = 720;
const sf::Int32 SCREEN_COLOR_DEPTH = 32;
const char* WINDOW_TITLE = "Hello World - SFML";

int main(int argc, char* argv[])
{
    static_cast<void>(argc);
    static_cast<void>(argv);
    sf::RenderWindow App(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR_DEPTH), WINDOW_TITLE);

    Game game;

    if (!game.init()) {
        return 1;
    }

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
                case sf::Keyboard::Space:
                    // captures.push_back(std::make_pair(0, playClock.restart().asMilliseconds()));
                    game.kick();
                    break;

                case sf::Keyboard::S:
                    // captures.push_back(std::make_pair(1, playClock.restart().asMilliseconds()));
                    game.snare();
                    break;

                case sf::Keyboard::P:
                    game.hihat();
                    break;

                case sf::Keyboard::H:
                    game.shaman();
                    break;

                case sf::Keyboard::G:
                    game.reset();
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

        game.tick(deltaTime);
        game.render(&App);
        App.display();
    }

    return 0;
}
