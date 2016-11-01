#ifndef CORE_ANIMATIONS_SLEEP_HPP_
#define CORE_ANIMATIONS_SLEEP_HPP_

#include <algorithm>
#include <core/animation.hpp>

template <typename Value>
class Sleep: public Animation<Value>
{
public:
    Sleep(int32_t initialTimeout):
        m_initialTimeout(initialTimeout),
        m_currentTimeout(initialTimeout),
        m_currentValue()
    {}

    virtual Value nextValue(const int32_t deltaTime) override
    {
        m_currentTimeout = std::max(0, m_currentTimeout - deltaTime);

        return m_currentValue;
    }

    virtual Value getCurrentValue() const override
    {
        return m_currentValue;
    }

    virtual bool isFinished() const override
    {
        return m_currentTimeout <= 0;
    }

    virtual void reset(const Value &value) override
    {
        m_currentValue = value;
        m_currentTimeout = m_initialTimeout;
    }

private:
    const int32_t m_initialTimeout;
    int32_t m_currentTimeout;
    Value m_currentValue;
};

#endif  // CORE_ANIMATIONS_SLEEP_HPP_
