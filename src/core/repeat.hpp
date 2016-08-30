#ifndef REPEAT_HPP_
#define REPEAT_HPP_

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

    State nextState(const int32_t deltaTime) override
    {
        if (m_animation->isFinished() && m_currentCounter > 0) {
            --m_currentCounter;
            m_animation->reset();
        }

        return m_animation->nextState(deltaTime);
    }

    State getCurrentState() const override
    {
        return m_animation->getCurrentState();
    }

    bool isFinished() const override
    {
        return m_currentCounter <= 0;
    }

    void reset() override
    {
        m_currentCounter = m_initialCounter;
        m_animation->reset();
    }

private:
    const int m_initialCounter;
    AnimationPtr<State> m_animation;
    int m_currentCounter;
};


#endif  // REPEAT_HPP_
