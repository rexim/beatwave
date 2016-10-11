#ifndef CORE_DSL_HPP_
#define CORE_DSL_HPP_

#include <core/lineartransitionbuilder.hpp>
#include <core/seqcombinatorbuilder.hpp>
#include <core/forever.hpp>
#include <core/repeat.hpp>
#include <core/set.hpp>

namespace dsl {

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
LinearTransitionBuilder::OpenDuring<State, false> to(const State &finalState)
{
    return LinearTransitionBuilder::OpenDuring<State, false>(finalState);
}

template <typename State>
LinearTransitionBuilder::OpenDuring<State, true> by(const State &deltaState)
{
    return LinearTransitionBuilder::OpenDuring<State, true>(deltaState);
}


// TODO(#87): implement by()

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

#endif  // CORE_DSL_HPP_
