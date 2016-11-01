#ifndef HELPERS_COUNTANIMATION_HPP_
#define HELPERS_COUNTANIMATION_HPP_

#include <iostream>
#include <core/animation.hpp>

template <bool Closed>
class CountAnimation: public Animation<int>
{
public:
    CountAnimation(int initialValue, int finalValue):
        m_initialValue(initialValue),
        m_finalValue(finalValue),
        m_currentValue(initialValue)
    {}

    virtual int nextValue(const int32_t) override
    {
        if (!isFinished()) {
            return ++m_currentValue;
        } else {
            return getCurrentValue();
        }
    }

    virtual int getCurrentValue() const override
    {
        return m_currentValue;
    }

    virtual bool isFinished() const override
    {
        return m_currentValue >= m_finalValue;
    }

    virtual void reset(const int &initialValue) override
    {
        std::cout << "CountAnimation::reset()" << std::endl;

        if(!Closed) {
            m_currentValue = initialValue;
        } else {
            std::cout << "khooy" << std::endl;
            m_currentValue = m_initialValue;
        }
    }

private:
    const int m_initialValue;
    const int m_finalValue;
    int m_currentValue;
};

#endif  // HELPERS_COUNTANIMATION_HPP_
