#ifndef CORE_ANIMATED_HPP_
#define CORE_ANIMATED_HPP_

#include <memory>
#include <core/animation.hpp>

template <typename T>
class Animated
{
public:
    using type = T;

    Animated(const Animated&) = delete;
    Animated(Animated&&) = default;

    explicit Animated(const T &value = T()):
        m_value(value),
        m_animation(nullptr)
    {}

    T value() const
    {
        return m_value;
    }

    void stop()
    {
        m_animation.reset();
    }

    void animate(AnimationPtr<T> &&animation)
    {
        if (animation != nullptr) {
            m_animation = std::move(animation);
            m_animation->reset(m_value);
            m_value = m_animation->getCurrentState();
        }
    }

    void tick(int32_t deltaTime)
    {
        if (m_animation != nullptr && !m_animation->isFinished()) {
            m_value = m_animation->nextState(deltaTime);
        }
    }

private:
    T m_value;
    AnimationPtr<T> m_animation;
};

#endif  // CORE_ANIMATED_HPP_
