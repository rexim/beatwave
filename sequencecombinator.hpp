#ifndef SEQUENCECOMBINATOR_HPP_
#define SEQUENCECOMBINATOR_HPP_

#include <vector>
#include "./animation.hpp"

template <typename State>
class SequenceCombinator: public Animation<State>
{
public:
    SequenceCombinator(std::vector<AnimationPtr<State>> &&animations):
        m_animations(std::move(animations)),
        m_currentAnimation(0)
    {}

    State nextState(const sf::Int32 deltaTime)
    {
        if (!isFinished()) {
            if (!m_animations[m_currentAnimation]->isFinished()) {
                return m_animations[m_currentAnimation]->nextState(deltaTime);
            } else {
                ++m_currentAnimation;
                if (!isFinished()) {
                    return m_animations[m_currentAnimation]->getCurrentState();
                }
            }
        }

        return m_animations.back()->getCurrentState();
    }

    State getCurrentState() const
    {
        return m_animations[m_currentAnimation]->getCurrentState();
    }

    bool isFinished() const
    {
        return m_currentAnimation >= m_animations.size();
    }

private:
    std::vector<AnimationPtr<State>> m_animations;
    size_t m_currentAnimation;
};

#endif  // SEQUENCECOMBINATOR_HPP_
