#ifndef CORE_ANIMATIONS_SLEEP_HPP_
#define CORE_ANIMATIONS_SLEEP_HPP_

#include <core/animation.hpp>

template <typename Value>
class Sleep: public Animation<Value>
{
public:
    Sleep(int32_t initialTimeout):
        m_initialTimeout(initialTimeout),
        m_currenTimeout(initialTimeout)
    {}

    virtual Value nextValue(const int32_t deltaTime) override
    {
        return Value();
    }

    virtual Value getCurrentValue() const override
    {
        return Value();
    }

    virtual bool isFinished() const override
    {
        return false;
    }

    virtual void reset(const Value &value) override
    {
    }

private:
    const int32_t m_initialTimeout;
    int32_t m_currenTimeout;
};

#endif  // CORE_ANIMATIONS_SLEEP_HPP_
