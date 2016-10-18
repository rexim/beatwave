#ifndef CORE_ANIMATIONS_NIL_HPP_
#define CORE_ANIMATIONS_NIL_HPP_

#include <core/animation.hpp>

template <typename Value>
class Nil: public Animation<Value>
{
public:
    Nil()
    {}

    virtual Value nextValue(const int32_t) override
    {
        return Value();
    }

    virtual Value getCurrentValue() const override
    {
        return Value();
    }

    virtual bool isFinished() const override
    {
        return true;
    }

    virtual void reset(const Value&) override
    {}
};

#endif  // CORE_ANIMATIONS_NIL_HPP_
