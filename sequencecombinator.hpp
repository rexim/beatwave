#ifndef SEQUENCECOMBINATOR_HPP_
#define SEQUENCECOMBINATOR_HPP_

#include <vector>
#include <initializer_list>
#include "./animation.hpp"

template <typename State>
class SequenceCombinator: public Animation<State>
{
public:
    SequenceCombinator(std::initializer_list<Animation<State>*> animations):
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

template <typename State>
class seq
{
public:
    seq(std::initializer_list<Animation<State>*> animations):
        sequenceCombinator(new SequenceCombinator<State>(animations))
    {}

    operator SequenceCombinator<State>*() {
        return sequenceCombinator;
    }

private:
    SequenceCombinator<State> *sequenceCombinator;
};

#endif  // SEQUENCECOMBINATOR_HPP_
