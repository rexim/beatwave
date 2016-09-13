#ifndef ANIMATEDTUPLE_HPP_
#define ANIMATEDTUPLE_HPP_

#include <tuple>

template <typename ...Tp>
using AnimatedTuple = std::tuple<Animated<Tp>...>;

// FIXME(#57): generalize tuple iteration process
template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
iterateTick(AnimatedTuple<Tp...>&, int32_t)
{}

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type
iterateTick(AnimatedTuple<Tp...>& properties, int32_t deltaTime)
{
    std::get<I>(properties).tick(deltaTime);
    iterateTick<I + 1, Tp...>(properties, deltaTime);
}

#endif  // ANIMATEDTUPLE_HPP_
