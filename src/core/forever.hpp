#ifndef FOREVER_HPP_
#define FOREVER_HPP_

#include <memory>
#include <core/animation.hpp>

template <typename State>
class Forever: public Animation<State>
{
public:
    Forever(AnimationPtr<State> &&animation):
        m_animation(std::move(animation))
    {}

    virtual State nextState(const int32_t deltaTime) override
    {
        if (m_animation->isFinished()) {
            m_animation->reset(m_animation->getCurrentState());
        }

        return m_animation->nextState(deltaTime);
    }

    virtual State getCurrentState() const override
    {
        return m_animation->getCurrentState();
    }

    virtual bool isFinished() const override
    {
        return false;
    }

    virtual void reset(const State &state) override
    {
        m_animation->reset(state);
    }

private:
    AnimationPtr<State> m_animation;
};



#endif  // FOREVER_HPP_
