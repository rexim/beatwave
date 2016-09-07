#ifndef ANIMATEDGROUP_HPP_
#define ANIMATEDGROUP_HPP_

#include <tuple>
#include <core/animated.hpp>

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

template <typename ...Tp>
class AnimatedGroup
{
public:
    template <size_t I>
    using AnimatedElement = typename std::tuple_element<I, AnimatedTuple<Tp...>>::type::type;

    AnimatedGroup(Tp... properties):
        m_properties(Animated<Tp>(properties)...)
    {}

    void tick(int32_t deltaTime)
    {
        iterateTick<0, Tp...>(m_properties, deltaTime);
    }

    // FIXME(#58): Implement stop() operation for AnimatedGroup

    template <size_t I>
    void animate(AnimationPtr<AnimatedElement<I>> &&animation)
    {
        std::get<I>(m_properties).animate(std::move(animation));
    }

    template <size_t I>
    AnimatedElement<I> value() const
    {
        return std::get<I>(m_properties).value();
    }

private:
    AnimatedTuple<Tp...> m_properties;
};

#endif  // ANIMATEDGROUP_HPP_
