#ifndef CORE_SET_HPP_
#define CORE_SET_HPP_

#include <iostream>

template <typename State>
class Set: public Animation<State>
{
public:
    Set(const State &state):
        m_state(state)
    {}

    virtual State nextState(const int32_t) override
    {
        return m_state;
    }

    virtual State getCurrentState() const override
    {
        return m_state;
    }

    virtual bool isFinished() const override
    {
        return false;
    }

    virtual void reset(const State&) override
    {}

private:
    const State m_state;
};

#endif  // CORE_SET_HPP_
