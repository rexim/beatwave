#ifndef SEQCOMBINATOR_HPP_
#define SEQCOMBINATOR_HPP_

#include <vector>
#include <initializer_list>

#include <core/animation.hpp>

template <typename State>
class SeqCombinator: public Animation<State>
{
public:
    // TODO: check if there are no animation
    SeqCombinator(std::vector<AnimationPtr<State>> &&animations):
        m_animations(std::move(animations)),
        m_currentAnimation(0)
    {}

    virtual State nextState(const int32_t deltaTime) override
    {
        if (!isFinished()) {
            if (!m_animations[m_currentAnimation]->isFinished()) {
                return m_animations[m_currentAnimation]->nextState(deltaTime);
            } else {
                const State previousState = m_animations[m_currentAnimation]->getCurrentState();
                m_currentAnimation++;
                if (!isFinished()) {
                    m_animations[m_currentAnimation]->reset(previousState);
                    return m_animations[m_currentAnimation]->getCurrentState();
                }
            }
        }

        return m_animations.back()->getCurrentState();
    }

    virtual State getCurrentState() const override
    {
        if (isFinished()) {
            return m_animations.back()->getCurrentState();
        } else {
            return m_animations[m_currentAnimation]->getCurrentState();
        }
    }

    virtual bool isFinished() const override
    {
        return m_currentAnimation >= m_animations.size();
    }

    virtual void reset(const State &state) override
    {
        m_currentAnimation = 0;
        m_animations[m_currentAnimation]->reset(state);
    }

private:
    std::vector<AnimationPtr<State>> m_animations;
    size_t m_currentAnimation;
};

#endif  // SEQCOMBINATOR_HPP_
