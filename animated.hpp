#ifndef ANIMATED_HPP_
#define ANIMATED_HPP_

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
        if (m_transition != nullptr) {
            delete m_transition;
            m_transition = nullptr;
        }

        m_transition = transition;
    }

    void tick(sf::Int32 deltaTime)
    {
        if (m_transition != nullptr) {
            if (!m_transition.isFinished()) {
                m_value = m_transition->nextState(deltaTime);
            } else {
                delete m_transition;
                m_transition = nullptr;
            }
        }
    }

private:
    T m_value;
    Transition<T> *m_transition;
};

#endif  // ANIMATED_HPP_
