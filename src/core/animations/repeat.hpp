#ifndef CORE_ANIMATIONS_REPEAT_HPP_
#define CORE_ANIMATIONS_REPEAT_HPP_

#include <algorithm>
#include <memory>

#include <core/animation.hpp>

template <typename State>
class Repeat: public Animation<State>
{
public:
    Repeat(int counter, AnimationPtr<State> &&animation):
        m_initialCounter(std::max(0, counter)),
        m_animation(std::move(animation)),
        m_currentCounter(m_initialCounter)
    {}

    virtual State nextState(const int32_t deltaTime) override
    {
        if (m_animation->isFinished() && m_currentCounter > 0) {
            --m_currentCounter;
            m_animation->reset(m_animation->getCurrentState());
        }

        return m_animation->nextState(deltaTime);
    }

    virtual State getCurrentState() const override
    {
        return m_animation->getCurrentState();
    }

    virtual bool isFinished() const override
    {
        return m_currentCounter <= 0;
    }

    virtual void reset(const State &state) override
    {
        m_currentCounter = m_initialCounter;
        m_animation->reset(state);
    }

private:
    const int m_initialCounter;
    AnimationPtr<State> m_animation;
    int m_currentCounter;
};


#endif  // CORE_ANIMATIONS_REPEAT_HPP_
