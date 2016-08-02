#ifndef SEQCOMBINATOR_HPP_
#define SEQCOMBINATOR_HPP_

#include <vector>
#include <initializer_list>
#include <animation.hpp>

template <typename State>
class SeqCombinator: public Animation<State>
{
public:
    SeqCombinator(std::initializer_list<Animation<State>*> animations):
        m_currentAnimation(0)
    {
        for (auto animation: animations) {
            m_animations.push_back(std::unique_ptr<Animation<State>>(animation));
        }
    }

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
    std::vector<std::unique_ptr<Animation<State>>> m_animations;
    size_t m_currentAnimation;
};

#endif  // SEQCOMBINATOR_HPP_
