#ifndef CORE_ANIMATIONS_OPENLINEARTRANSITION_HPP_
#define CORE_ANIMATIONS_OPENLINEARTRANSITION_HPP_

#include <core/animations/lineartransition.hpp>
#include <core/animation.hpp>

template <typename Value, bool Relative>
class OpenLinearTransition: public Animation<Value>
{
public:
    OpenLinearTransition(int32_t transitionTime,
                         const Value &value):
        m_transitionTime(transitionTime),
        m_value(value),
        m_linearTransition(nullptr)
    {}

    virtual Value nextValue(const int32_t deltaTime) override
    {
        if (m_linearTransition) {
            return m_linearTransition->nextValue(deltaTime);
        } else {
            return m_value;
        }
    }

    virtual Value getCurrentValue() const override
    {
        if (m_linearTransition) {
            return m_linearTransition->getCurrentValue();
        } else {
            return m_value;
        }
    }

    virtual bool isFinished() const override
    {
        return !m_linearTransition || m_linearTransition->isFinished();
    }

    virtual void reset(const Value &initialValue) override
    {
        m_linearTransition.reset(new LinearTransition<Value>(initialValue,
                                                             m_transitionTime,
                                                             Relative ? initialValue + m_value : m_value));
    }

private:
    const int32_t m_transitionTime;
    const Value m_value;
    AnimationPtr<Value> m_linearTransition;
};

#endif  // CORE_ANIMATIONS_OPENLINEARTRANSITION_HPP_
