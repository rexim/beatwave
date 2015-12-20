#ifndef ANIMATED_HPP_
#define ANIMATED_HPP_

#include <memory>
#include "./transition.hpp"

template <typename T>
class Animated
{
public:
    Animated(const Animated&) = delete;

    Animated(const T &value):
        m_value(value),
        m_transition(nullptr)
    {}

    ~Animated()
    {
        if (m_transition != nullptr) {
            delete m_transition;
            m_transition = nullptr;
        }
    }

    T getValue() const
    {
        return value;
    }

    void setTransition(Transition<T> *transition)
    {
        m_transition = transition;
    }

    void tick(sf::Int32 deltaTime)
    {
        if (m_transition != nullptr && !m_transition->isFinished()) {
            m_value = m_transition->nextState(deltaTime);
        }
    }

private:
    T m_value;
    std::unique_ptr<Transition<T>> m_transition;
};

#endif  // ANIMATED_HPP_
