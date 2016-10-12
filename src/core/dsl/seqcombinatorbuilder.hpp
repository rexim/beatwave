#ifndef CORE_DSL_SEQCOMBINATORBUILDER_HPP_
#define CORE_DSL_SEQCOMBINATORBUILDER_HPP_

#include <core/animations/seqcombinator.hpp>

template <typename Value>
class SeqCombinatorBuilder
{
public:
    SeqCombinatorBuilder(AnimationPtr<Value> &&animation)
    {
        m_animations.push_back(std::move(animation));
    }

    SeqCombinatorBuilder<Value> &then(AnimationPtr<Value> &&animation)
    {
        m_animations.push_back(std::move(animation));
        return *this;
    }

    AnimationPtr<Value> end()
    {
        return AnimationPtr<Value>(new SeqCombinator<Value>(std::move(m_animations)));
    }

private:
    std::vector<AnimationPtr<Value>> m_animations;
};

#endif  // CORE_DSL_SEQCOMBINATORBUILDER_HPP_
