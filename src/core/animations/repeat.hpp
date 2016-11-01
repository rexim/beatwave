#ifndef CORE_ANIMATIONS_REPEAT_HPP_
#define CORE_ANIMATIONS_REPEAT_HPP_

#include <algorithm>
#include <memory>

#include <core/animation.hpp>

template <typename Value>
class Repeat: public Animation<Value>
{
public:
    Repeat(int counter, AnimationPtr<Value> &&animation):
        m_initialCounter(std::max(0, counter)),
        m_animation(std::move(animation)),
        m_currentCounter(m_initialCounter)
    {}

    virtual Value nextValue(const int32_t deltaTime) override
    {
        if (isFinished()) {
            return m_animation->getCurrentValue();
        }

        if (m_animation->isFinished()) {
            --m_currentCounter;

            if (isFinished()) {
                return m_animation->getCurrentValue();
            } else {
                m_animation->reset(m_animation->getCurrentValue());
                return m_animation->getCurrentValue();
            }
        } else {
            return m_animation->nextValue(deltaTime);
        }
    }

    virtual Value getCurrentValue() const override
    {
        return m_animation->getCurrentValue();
    }

    virtual bool isFinished() const override
    {
        return m_currentCounter <= 0;
    }

    virtual void reset(const Value &value) override
    {
        m_currentCounter = m_initialCounter;
        m_animation->reset(value);
    }

private:
    const int m_initialCounter;
    AnimationPtr<Value> m_animation;
    int m_currentCounter;
};


#endif  // CORE_ANIMATIONS_REPEAT_HPP_
