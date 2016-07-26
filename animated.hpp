#ifndef ANIMATED_HPP_
#define ANIMATED_HPP_

#include <memory>
#include "animation.hpp"

template <typename T>
class Animated
{
public:
    Animated(const Animated&) = delete;

    Animated(const T &value = T()):
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

    void animate(Animation<T> *animation)
    {
        m_animation.reset(animation);

        if (!m_animation->isFinished()) {
            m_value = m_animation->getCurrentState();
        }
    }

    void tick(sf::Int32 deltaTime)
    {
        if (m_animation != nullptr && !m_animation->isFinished()) {
            m_value = m_animation->nextState(deltaTime);
        }
    }

private:
    T m_value;
    std::unique_ptr<Animation<T>> m_animation;
};

#endif  // ANIMATED_HPP_
