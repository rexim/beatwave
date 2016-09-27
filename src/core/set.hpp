#ifndef SET_HPP_
#define SET_HPP_

#include <iostream>

template <typename State>
class Set: public Animation<State>
{
public:
    Set(const State &state):
        m_state(state),
        m_finished(false)
    {}

    virtual State nextState(const int32_t) override
    {
        m_finished = true;
        return m_state;
    }

    virtual State getCurrentState() const override
    {
        return m_state;
    }

    virtual bool isFinished() const override
    {
        return m_finished;
    }

    virtual void reset(const State&) override
    {
        m_finished = false;
    }

private:
    const State m_state;
    bool m_finished;
};

#endif  // SET_HPP_
