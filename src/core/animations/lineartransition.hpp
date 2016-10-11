#ifndef CORE_ANIMATIONS_LINEARTRANSITION_HPP_
#define CORE_ANIMATIONS_LINEARTRANSITION_HPP_

#include <core/animation.hpp>

template <typename Value>
class LinearTransition: public Animation<Value>
{
public:
    LinearTransition(const Value &initialValue,
                     int32_t transitionTime,
                     const Value &finalValue):
        m_initialValue(initialValue),
        m_transitionTime(transitionTime),
        m_currentValue(initialValue),
        m_timeLeft(transitionTime),
        m_finalValue(finalValue)
    {}

    virtual Value nextValue(const int32_t deltaTime) override
    {
        if (deltaTime < m_timeLeft) {
            Value deltaValue = (m_finalValue - m_currentValue) * ((deltaTime + .0f) / m_timeLeft);
            m_currentValue += deltaValue;
        } else {
            m_currentValue = m_finalValue;
        }

        m_timeLeft -= deltaTime;
        return getCurrentValue();
    }

    virtual Value getCurrentValue() const override
    {
        return m_currentValue;
    }

    virtual bool isFinished() const override
    {
        return m_timeLeft <= 0.0f;
    }

    virtual void reset(const Value&) override
    {
        m_currentValue = m_initialValue;
        m_timeLeft = m_transitionTime;
    }

private:
    const Value m_initialValue;
    const int32_t m_transitionTime;

    Value m_currentValue;
    int32_t m_timeLeft;
    const Value m_finalValue;
};

#endif  // CORE_ANIMATIONS_LINEARTRANSITION_HPP_
