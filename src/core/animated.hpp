#ifndef CORE_ANIMATED_HPP_
#define CORE_ANIMATED_HPP_

#include <memory>
#include <core/animation.hpp>

template <typename Value>
class Animated
{
public:
    using ValueType = Value;

    Animated(const Animated&) = delete;
    Animated(Animated&&) = default;

    explicit Animated(const Value &value = Value()):
        m_value(value),
        m_animation(nullptr)
    {}

    Value value() const
    {
        return m_value;
    }

    void stop()
    {
        m_animation.reset();
    }

    void animate(AnimationPtr<Value> &&animation)
    {
        if (animation != nullptr) {
            m_animation = std::move(animation);
            m_animation->reset(m_value);
            m_value = m_animation->getCurrentValue();
        }
    }

    void tick(int32_t deltaTime)
    {
        if (m_animation != nullptr && !m_animation->isFinished()) {
            m_value = m_animation->nextValue(deltaTime);
        }
    }

private:
    Value m_value;
    AnimationPtr<Value> m_animation;
};

#endif  // CORE_ANIMATED_HPP_
