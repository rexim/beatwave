#ifndef CORE_ANIMATIONS_FOREVER_HPP_
#define CORE_ANIMATIONS_FOREVER_HPP_

#include <memory>
#include <core/animation.hpp>

template <typename Value>
class Forever: public Animation<Value>
{
public:
    Forever(AnimationPtr<Value> &&animation):
        m_animation(std::move(animation))
    {}

    virtual Value nextValue(const int32_t deltaTime) override
    {
        if (m_animation->isFinished()) {
            m_animation->reset(m_animation->getCurrentValue());
            return m_animation->getCurrentValue();
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
        return false;
    }

    virtual void reset(const Value &value) override
    {
        m_animation->reset(value);
    }

private:
    AnimationPtr<Value> m_animation;
};



#endif  // CORE_ANIMATIONS_FOREVER_HPP_
