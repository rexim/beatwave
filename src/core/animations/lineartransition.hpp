#ifndef CORE_ANIMATIONS_LINEARTRANSITION_HPP_
#define CORE_ANIMATIONS_LINEARTRANSITION_HPP_

#include <core/animation.hpp>

template <typename State>
class LinearTransition: public Animation<State>
{
public:
    LinearTransition(const State &initialState,
                     int32_t transitionTime,
                     const State &finalState):
        m_initialState(initialState),
        m_transitionTime(transitionTime),
        m_currentState(initialState),
        m_timeLeft(transitionTime),
        m_finalState(finalState)
    {}

    virtual State nextState(const int32_t deltaTime) override
    {
        if (deltaTime < m_timeLeft) {
            State deltaState = (m_finalState - m_currentState) * ((deltaTime + .0f) / m_timeLeft);
            m_currentState += deltaState;
        } else {
            m_currentState = m_finalState;
        }

        m_timeLeft -= deltaTime;
        return m_currentState;
    }

    virtual State getCurrentState() const override
    {
        return m_currentState;
    }

    virtual bool isFinished() const override
    {
        return m_timeLeft <= 0.0f;
    }

    virtual void reset(const State&) override
    {
        m_currentState = m_initialState;
        m_timeLeft = m_transitionTime;
    }

private:
    const State m_initialState;
    const int32_t m_transitionTime;

    State m_currentState;
    int32_t m_timeLeft;
    const State m_finalState;
};

#endif  // CORE_ANIMATIONS_LINEARTRANSITION_HPP_
