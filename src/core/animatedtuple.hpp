#ifndef CORE_ANIMATEDTUPLE_HPP_
#define CORE_ANIMATEDTUPLE_HPP_

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

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
iterateTick(std::tuple<Tp...>&, int32_t)
{}

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type
iterateTick(std::tuple<Tp...>& properties, int32_t deltaTime)
{
    std::get<I>(properties).tick(deltaTime);
    iterateTick<I + 1, Tp...>(properties, deltaTime);
}

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
iterateStop(AnimatedTuple<Tp...>&)
{}

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type
iterateStop(AnimatedTuple<Tp...>& properties)
{
    std::get<I>(properties).stop();
    iterateStop<I + 1, Tp...>(properties);
}

template <std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
iterateRender(const std::tuple<Tp...>&, sf::RenderTarget*)
{}

template <std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type
iterateRender(const std::tuple<Tp...> &members, sf::RenderTarget* renderTarget)
{
    std::get<I>(members).render(renderTarget);
    iterateRender<I + 1, Tp...>(members, renderTarget);
}

#endif  // CORE_ANIMATEDTUPLE_HPP_
