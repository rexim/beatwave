#ifndef DSL_HPP_
#define DSL_HPP_

#include <core/lineartransitionbuilder.hpp>
#include <core/seqcombinatorbuilder.hpp>
#include <core/forever.hpp>
#include <core/repeat.hpp>
#include <core/set.hpp>

namespace dsl {

template <typename State>
SeqCombinatorBuilder<State> start(AnimationPtr<State> &&animation)
{
    return SeqCombinatorBuilder<State>(std::move(animation));
}

template <typename State>
AnimationPtr<State> forever(AnimationPtr<State> &&animation)
{
    return AnimationPtr<State>(new Forever<State>(std::move(animation)));
}

// FIXME(#59): Strict argument order for LinearTransitionBuilder
template <typename T>
LinearTransitionBuilder<T> from(const T &initialState)
{
    return LinearTransitionBuilder<T>(initialState);
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
