#ifndef SEQUENCECOMBINATORBUILDER_HPP_
#define SEQUENCECOMBINATORBUILDER_HPP_

#include "./animation.hpp"
#include <vector>

template <typename State>
class SequenceCombinatorBuilder
{
public:
    SequenceCombinatorBuilder(AnimationPtr<State> &&animation)
    {
        m_animations.push_back(std::move(animation));
    }

    SequenceCombinatorBuilder<State> &then(AnimationPtr<State> &&animation)
    {
        m_animations.push_back(std::move(animation));
        return *this;
    }

    operator AnimationPtr<State>()
    {
        return AnimationPtr<State>(new SequenceCombinator<State>(std::move(m_animations)));
    }

private:
    std::vector<AnimationPtr<State>> m_animations;
};

template <typename State>
SequenceCombinatorBuilder<State> &seq(AnimationPtr<State> &&animation)
{
    return SequenceCombinatorBuilder<State>(std::move(animation));
}

#endif  // SEQUENCECOMBINATORBUILDER_HPP_
