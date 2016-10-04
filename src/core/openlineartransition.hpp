#ifndef OPENLINEARTRANSITION_HPP_
#define OPENLINEARTRANSITION_HPP_

#include <core/lineartransition.hpp>
#include <core/animation.hpp>

template <typename State, bool Relative>
class OpenLinearTransition: public Animation<State>
{
public:
    OpenLinearTransition(int32_t transitionTime,
                         const State &state):
        m_transitionTime(transitionTime),
        m_state(state),
        m_linearTransition(nullptr)
    {}

    virtual State nextState(const int32_t deltaTime) override
    {
        if (m_linearTransition) {
            return m_linearTransition->nextState(deltaTime);
        } else {
            return m_state;
        }
    }

    virtual State getCurrentState() const override
    {
        if (m_linearTransition) {
            return m_linearTransition->getCurrentState();
        } else {
            return m_state;
        }
    }

    virtual bool isFinished() const override
    {
        return !m_linearTransition || m_linearTransition->isFinished();
    }

    virtual void reset(const State &initialState) override
    {
        m_linearTransition.reset(new LinearTransition<State>(initialState,
                                                             m_transitionTime,
                                                             Relative ? initialState + m_state : m_state));
    }

private:
    const int32_t m_transitionTime;
    const State m_state;
    AnimationPtr<State> m_linearTransition;
};

#endif  // OPENLINEARTRANSITION_HPP_
