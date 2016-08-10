#ifndef SEQCOMBINATORBUILDER_HPP_
#define SEQCOMBINATORBUILDER_HPP_

#include <core/seqcombinator.hpp>

template <typename State>
class SeqCombinatorBuilder
{
public:
    SeqCombinatorBuilder(Animation<State> *animation)
    {
        m_animations.push_back(AnimationPtr<State>(animation));
    }

    SeqCombinatorBuilder<State> &then(Animation<State> *animation)
    {
        m_animations.push_back(AnimationPtr<State>(animation));
        return *this;
    }

    operator Animation<State>*()
    {
        return new SeqCombinator<State>(std::move(m_animations));
    }

private:
    std::vector<AnimationPtr<State>> m_animations;
};

template <typename State>
SeqCombinatorBuilder<State> start(Animation<State> *animation)
{
    return SeqCombinatorBuilder<State>(animation);
}

#endif  // SEQCOMBINATORBUILDER_HPP_
