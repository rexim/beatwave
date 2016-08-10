#ifndef SEQCOMBINATORBUILDER_HPP_
#define SEQCOMBINATORBUILDER_HPP_

#include <core/seqcombinator.hpp>

template <typename State>
class SeqCombinatorBuilder
{
public:
    SeqCombinatorBuilder(AnimationPtr<State> &&animation)
    {
        m_animations.push_back(std::move(animation));
    }

    SeqCombinatorBuilder<State> &then(AnimationPtr<State> &&animation)
    {
        m_animations.push_back(std::move(animation));
        return *this;
    }

    operator AnimationPtr<State>()
    {
        return AnimationPtr<State>(new SeqCombinator<State>(std::move(m_animations)));
    }

private:
    std::vector<AnimationPtr<State>> m_animations;
};

template <typename State>
SeqCombinatorBuilder<State> start(AnimationPtr<State> &&animation)
{
    return SeqCombinatorBuilder<State>(std::move(animation));
}

#endif  // SEQCOMBINATORBUILDER_HPP_
