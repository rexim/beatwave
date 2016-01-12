#ifndef LINEARTRANSITION_HPP_
#define LINEARTRANSITION_HPP_

#include "./animation.hpp"

template <typename T>
class LinearTransition: public Animation<T>
{
public:
    LinearTransition(const T &initialState,
                     sf::Int32 transitionTime = 0,
                     const T &finalState = T()):
        currentState(initialState),
        timeLeft(transitionTime),
        finalState(finalState)
    {}

    virtual T nextState(const sf::Int32 deltaTime) override
    {
        if (deltaTime < timeLeft) {
            T deltaState = (finalState - currentState) * ((deltaTime + .0f) / timeLeft);
            currentState += deltaState;
        } else {
            currentState = finalState;
        }

        timeLeft -= deltaTime;
        return currentState;
    }

    virtual T getCurrentState() const override
    {
        return currentState;
    }

    virtual bool isFinished() const override
    {
        return timeLeft <= 0.0f;
    }

private:
    T currentState;
    sf::Int32 timeLeft;
    const T finalState;
};

#endif  // LINEARTRANSITION_HPP_
