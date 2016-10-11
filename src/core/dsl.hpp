#ifndef CORE_DSL_HPP_
#define CORE_DSL_HPP_

#include <core/dsl/lineartransitionbuilder.hpp>
#include <core/dsl/seqcombinatorbuilder.hpp>

#include <core/animations/forever.hpp>
#include <core/animations/repeat.hpp>
#include <core/animations/set.hpp>

namespace dsl {

template <typename Value>
SeqCombinatorBuilder<Value> begin(AnimationPtr<Value> &&animation)
{
    return SeqCombinatorBuilder<Value>(std::move(animation));
}

template <typename Value>
AnimationPtr<Value> forever(AnimationPtr<Value> &&animation)
{
    return AnimationPtr<Value>(new Forever<Value>(std::move(animation)));
}

template <typename T>
LinearTransitionBuilder::Toby<T> from(const T &initialValue)
{
    return LinearTransitionBuilder::Toby<T>(initialValue);
}

template <typename Value>
LinearTransitionBuilder::OpenDuring<Value, false> to(const Value &finalValue)
{
    return LinearTransitionBuilder::OpenDuring<Value, false>(finalValue);
}

template <typename Value>
LinearTransitionBuilder::OpenDuring<Value, true> by(const Value &deltaValue)
{
    return LinearTransitionBuilder::OpenDuring<Value, true>(deltaValue);
}

template <typename Value>
AnimationPtr<Value> repeat(int counter, AnimationPtr<Value> &&animation)
{
    return AnimationPtr<Value>(new Repeat<Value>(counter, std::move(animation)));
}

template <typename Value>
AnimationPtr<Value> set(const Value &value)
{
    return AnimationPtr<Value>(new Set<Value>(value));
}

}

#endif  // CORE_DSL_HPP_
