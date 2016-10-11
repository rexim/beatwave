#ifndef CORE_ANIMATIONS_SEQCOMBINATOR_HPP_
#define CORE_ANIMATIONS_SEQCOMBINATOR_HPP_

#include <vector>
#include <initializer_list>

#include <core/animation.hpp>

template <typename State>
class SeqCombinator: public Animation<State>
{
public:
    // TODO(#100): check for nullptr animations in the sequence
    SeqCombinator(std::vector<AnimationPtr<State>> &&animations):
        m_animations(std::move(animations)),
        m_currentAnimation(0)
    {}

    virtual State nextState(const int32_t deltaTime) override
    {
        if (m_animations.empty()) {
            return m_emptyPlaceholder;
        }

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
        if (m_animations.empty()) {
            return m_emptyPlaceholder;
        } else if (isFinished()) {
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
        if (m_animations.empty()) {
            m_emptyPlaceholder = state;
        } else {
            m_currentAnimation = 0;
            m_animations[m_currentAnimation]->reset(state);
        }
    }

private:
    std::vector<AnimationPtr<State>> m_animations;
    size_t m_currentAnimation;
    State m_emptyPlaceholder;
};

#endif  // CORE_ANIMATIONS_SEQCOMBINATOR_HPP_
