#include <istream>
#include <ostream>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "./state.hpp"

struct Transition
{
public:
    Transition(const State &initialState,
               sf::Int32 transitionTime,
               const State &finalState):
        currentState(initialState),
        timeLeft(transitionTime),
        finalState(finalState)
    {}

    State nextState(const sf::Int32 deltaTime)
    {
        std::cout << timeLeft << std::endl;
        if (deltaTime < timeLeft) {
            State deltaState = (finalState - currentState) * ((deltaTime + .0) / timeLeft);

            currentState = currentState + deltaState;
        } else {
            currentState = finalState;
        }

        timeLeft -= deltaTime;
        return currentState;
    }

    bool isFinished() const
    {
        return timeLeft <= 0.0f;
    }

    sf::Int32 getTimeLeft() const
    {
        return timeLeft;
    }

private:
    State currentState;
    sf::Int32 timeLeft;
    const State finalState;
};

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

    const State normalState(200.0f, 200.0f, 50.0f, 255.0f, 255.0f, 255.0f, 255.0f);
    Transition *transition = NULL;
    State state(200.0f, 200.0f, 50.0f, 255.0f, 255.0f, 255.0f, 255.0f);
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
                // std::cout << "JoystickButtonEvent: " << Event.joystickButton.button << std::endl;

                switch (Event.joystickButton.button) {
                case 0:
                    state.radius = 70.0f;
                    state.r = 255.0f;
                    state.g = 0.0f;
                    state.b = 0.0f;

                    if (transition != NULL) {
                        delete transition;
                    }
                    transition = new Transition(state, 300, normalState);

                    kickSound.play();
                    break;

                case 1:
                    state.radius = 70.0f;
                    state.r = 0.0f;
                    state.g = 255.0f;
                    state.b = 0.0f;

                    if (transition != NULL) {
                        delete transition;
                    }
                    transition = new Transition(state, 300, normalState);

                    snareSound.play();
                    break;

                case 2:
                    state.radius = 70.0f;
                    state.r = 0.0f;
                    state.g = 0.0f;
                    state.b = 255.0f;

                    if (transition != NULL) {
                        delete transition;
                    }
                    transition = new Transition(state, 300, normalState);

                    hihatSound.play();
                    break;

                default: {}
                }
            }
        }

        App.clear(sf::Color(0, 0, 0));
        
        if (transition != NULL) {
            state = transition->nextState(clock.getElapsedTime().asMilliseconds());

            if (transition->isFinished()) {
                delete transition;
                transition = NULL;
            }
        }
        App.draw(stateToCircle(state));

        App.display();
    }
 
    return 0;
}
