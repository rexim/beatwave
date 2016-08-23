#ifndef LINEARTRANSITIONBUILDER_HPP_
#define LINEARTRANSITIONBUILDER_HPP_

#include <core/lineartransition.hpp>

template <typename T>
class LinearTransitionBuilder
{
public:
    LinearTransitionBuilder(const T &initialState):
        m_initialState(initialState)
    {}

    LinearTransitionBuilder<T> &to(const T &finalState)
    {
        m_finalState = finalState;
        return *this;
    }

    LinearTransitionBuilder<T> &by(const T &deltaState)
    {
        m_finalState = m_initialState + deltaState;
        return *this;
    }

    LinearTransitionBuilder<T> &during(sf::Int32 transitionTime)
    {
        m_transitionTime = transitionTime;
        return *this;
    }

    operator AnimationPtr<T>() {
        return AnimationPtr<T>(new LinearTransition<T>(m_initialState, m_transitionTime, m_finalState));
    }

private:
    T m_initialState;
    T m_finalState;
    sf::Int32 m_transitionTime;
};


#endif  // LINEARTRANSITIONBUILDER_HPP_
