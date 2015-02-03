#include <istream>
#include <ostream>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct State {
    float x, y, radius, r, g, b, a;

    State(float x, float y, float radius,
          float r, float g, float b, float a):
        x(x), y(y), radius(radius),
        r(r), g(g), b(b), a(a)
    {}
};

State operator+(const State &s1,
                const State &s2)
{
    return State(s1.x + s2.x,
                 s1.y + s2.y,
                 s1.radius + s2.radius,
                 s1.r + s2.r,
                 s1.g + s2.g,
                 s1.b + s2.b,
                 s1.a + s2.a);
}

State operator-(const State &s1,
                const State &s2)
{
    return State(s1.x - s2.x,
                 s1.y - s2.y,
                 s1.radius - s2.radius,
                 s1.r - s2.r,
                 s1.g - s2.g,
                 s1.b - s2.b,
                 s1.a - s2.a);
}

State operator*(const State &state, const float factor)
{
    return State(state.x * factor,
                 state.y * factor,
                 state.radius * factor,
                 state.r * factor,
                 state.g * factor,
                 state.b * factor,
                 state.a * factor);
}

sf::CircleShape stateToCircle(const State &state)
{
    sf::CircleShape circle(state.radius);
    circle.setFillColor(sf::Color(state.r, state.g, state.b, state.a));
    circle.setPosition(state.x - state.radius / 2.0f, state.y - state.radius / 2.0f);
    return circle;
}

std::ostream &operator<<(std::ostream &os, const State &state)
{
    os << "("
       << state.x << ", "
       << state.y << ", "
       << state.radius << ", "
       << state.r << ", "
       << state.g << ", "
       << state.b << ", "
       << state.a
       << ")";
    return os;
}

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
