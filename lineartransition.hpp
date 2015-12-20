#ifndef LINEARTRANSITION_HPP_
#define LINEARTRANSITION_HPP_

#include "./animation.hpp"

template <typename T>
class LinearTransition: public Animation<T>
{
public:
    LinearTransition(const T &initialState,
               sf::Int32 transitionTime,
               const T &finalState):
        currentState(initialState),
        timeLeft(transitionTime),
        finalState(finalState)
    {}

    T nextState(const sf::Int32 deltaTime) override
    {
        if (deltaTime < timeLeft) {
            T deltaState = (finalState - currentState) * ((deltaTime + .0) / timeLeft);

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
    T currentState;
    sf::Int32 timeLeft;
    const T finalState;
};

template <typename T>
Animation<T> *moveTo(const T &initialState, sf::Int32 transitionTime, const T &finalState)
{
    return new LinearTransition<T>(initialState, 
                                   transitionTime, 
                                   finalState);
}

template <typename T>
Animation<T> *moveBy(const T &initialState, sf::Int32 transitionTime, const T &deltaState)
{
    return new LinearTransition<T>(initialState, 
                                   transitionTime, 
                                   initialState + deltaState);
}

#endif  // LINEARTRANSITION_HPP_
