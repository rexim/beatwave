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

    State nextState(const sf::Int32 deltaTime) override
    {
        if (m_animation->isFinished()) {
            m_animation->reset();
        }

        return m_animation->nextState(deltaTime);
    }

    State getCurrentState() const override
    {
        return m_animation->getCurrentState();
    }

    bool isFinished() const override
    {
        return false;
    }

    void reset() override
    {}

private:
    AnimationPtr<State> m_animation;
};


template <typename State>
AnimationPtr<State> forever(AnimationPtr<State> &&animation)
{
    return AnimationPtr<State>(new Forever<State>(std::move(animation)));
}

#endif  // FOREVER_HPP_
