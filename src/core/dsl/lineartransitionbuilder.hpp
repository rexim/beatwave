#ifndef CORE_DSL_LINEARTRANSITIONBUILDER_HPP_
#define CORE_DSL_LINEARTRANSITIONBUILDER_HPP_

#include <core/animations/openlineartransition.hpp>

namespace LinearTransitionBuilder {

template <typename T>
class During
{
public:
    During(const T &initialValue, const T &finalValue):
        m_initialValue(initialValue), m_finalValue(finalValue)
    {}

    AnimationPtr<T> during(int32_t transitionTime)
    {
        return AnimationPtr<T>(new LinearTransition<T>(m_initialValue,
                                                       transitionTime,
                                                       m_finalValue));
    }

private:
    const T m_initialValue;
    const T m_finalValue;
};

template <typename Value, bool Relative>
class OpenDuring
{
public:
    OpenDuring(const Value &finalValue):
        m_finalValue(finalValue)
    {}

    AnimationPtr<Value> during(int32_t transitionTime)
    {
        return AnimationPtr<Value>(new OpenLinearTransition<Value, Relative>(transitionTime,
                                                                             m_finalValue));
    }

private:
    const Value m_finalValue;
};

template <typename T>
class Toby
{
public:
    Toby(const T &initialValue):
        m_initialValue(initialValue)
    {}

    During<T> to(const T &finalValue)
    {
        return During<T>(m_initialValue, finalValue);
    }

    During<T> by(const T &deltaValue)
    {
        return During<T>(m_initialValue, m_initialValue + deltaValue);
    }

private:
    const T m_initialValue;
};

}  // namespace LinearTransitionBuilder

#endif  // CORE_DSL_LINEARTRANSITIONBUILDER_HPP_
