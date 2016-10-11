#ifndef CORE_ANIMATIONS_SET_HPP_
#define CORE_ANIMATIONS_SET_HPP_

#include <iostream>

template <typename Value>
class Set: public Animation<Value>
{
public:
    Set(const Value &value):
        m_value(value)
    {}

    virtual Value nextValue(const int32_t) override
    {
        return m_value;
    }

    virtual Value getCurrentValue() const override
    {
        return m_value;
    }

    virtual bool isFinished() const override
    {
        return false;
    }

    virtual void reset(const Value&) override
    {}

private:
    const Value m_value;
};

#endif  // CORE_ANIMATIONS_SET_HPP_
