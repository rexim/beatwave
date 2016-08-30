#ifndef LINEARTRANSITION_HPP_
#define LINEARTRANSITION_HPP_

#include <core/animation.hpp>

template <typename T>
class LinearTransition: public Animation<T>
{
public:
    LinearTransition(const T &initialState,
                     int32_t transitionTime = 0,
                     const T &finalState = T()):
        m_initialState(initialState),
        m_transitionTime(transitionTime),
        m_currentState(initialState),
        m_timeLeft(transitionTime),
        m_finalState(finalState)
    {}

    virtual T nextState(const int32_t deltaTime) override
    {
        if (deltaTime < m_timeLeft) {
            T deltaState = (m_finalState - m_currentState) * ((deltaTime + .0f) / m_timeLeft);
            m_currentState += deltaState;
        } else {
            m_currentState = m_finalState;
        }

        m_timeLeft -= deltaTime;
        return m_currentState;
    }

    virtual T getCurrentState() const override
    {
        return m_currentState;
    }

    virtual bool isFinished() const override
    {
        return m_timeLeft <= 0.0f;
    }

    virtual void reset() override
    {
        m_currentState = m_initialState;
        m_timeLeft = m_transitionTime;
    }

private:
    const T m_initialState;
    const int32_t m_transitionTime;

    T m_currentState;
    int32_t m_timeLeft;
    const T m_finalState;
};

#endif  // LINEARTRANSITION_HPP_
