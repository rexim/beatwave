#ifndef LINEARTRANSITION_HPP_
#define LINEARTRANSITION_HPP_

#include "./transition.hpp"

template <typename State>
class LinearTransition: public Transition<State>
{
public:
    LinearTransition(const State &initialState,
               sf::Int32 transitionTime,
               const State &finalState):
        currentState(initialState),
        timeLeft(transitionTime),
        finalState(finalState)
    {}

    State nextState(const sf::Int32 deltaTime) override
    {
        if (deltaTime < timeLeft) {
            State deltaState = (finalState - currentState) * ((deltaTime + .0) / timeLeft);

            currentState = currentState + deltaState;
        } else {
            currentState = finalState;
        }

        timeLeft -= deltaTime;
        return currentState;
    }

    bool isFinished() const override
    {
        return timeLeft <= 0.0f;
    }

private:
    State currentState;
    sf::Int32 timeLeft;
    const State finalState;
};

#endif  // LINEARTRANSITION_HPP_
