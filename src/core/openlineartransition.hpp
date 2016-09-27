#ifndef OPENLINEARTRANSITION_HPP_
#define OPENLINEARTRANSITION_HPP_

#include <core/lineartransition.hpp>
#include <core/animation.hpp>

template <typename State>
class OpenLinearTransition: public Animation<State>
{
public:
    OpenLinearTransition(int32_t transitionTime,
                         const State &finalState):
        m_transitionTime(transitionTime),
        m_finalState(finalState),
        m_linearTransition(nullptr)
    {}

    virtual State nextState(const int32_t deltaTime) override
    {
        if (m_linearTransition) {
            return m_linearTransition->nextState(deltaTime);
        } else {
            return m_finalState;
        }
    }

    virtual State getCurrentState() const override
    {
        if (m_linearTransition) {
            return m_linearTransition->getCurrentState();
        } else {
            return m_finalState;
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
                                                             m_finalState));
    }

private:
    const int32_t m_transitionTime;
    const State m_finalState;
    AnimationPtr<State> m_linearTransition;
};

#endif  // OPENLINEARTRANSITION_HPP_
