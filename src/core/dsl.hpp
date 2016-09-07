#ifndef DSL_HPP_
#define DSL_HPP_

#include <core/lineartransitionbuilder.hpp>
#include <core/seqcombinatorbuilder.hpp>
#include <core/forever.hpp>
#include <core/repeat.hpp>
#include <core/set.hpp>

namespace dsl {

// FIXME(#60): Immitate a pascal-style block of code in SeqCombinatorBuilder
template <typename State>
SeqCombinatorBuilder<State> begin(AnimationPtr<State> &&animation)
{
    return SeqCombinatorBuilder<State>(std::move(animation));
}

template <typename State>
AnimationPtr<State> forever(AnimationPtr<State> &&animation)
{
    return AnimationPtr<State>(new Forever<State>(std::move(animation)));
}

template <typename T>
LinearTransitionBuilder::Toby<T> from(const T &initialState)
{
    return LinearTransitionBuilder::Toby<T>(initialState);
}

template <typename State>
AnimationPtr<State> repeat(int counter, AnimationPtr<State> &&animation)
{
    return AnimationPtr<State>(new Repeat<State>(counter, std::move(animation)));
}

template <typename State>
AnimationPtr<State> set(const State &state)
{
    return AnimationPtr<State>(new Set<State>(state));
}

}

#endif  // DSL_HPP_
