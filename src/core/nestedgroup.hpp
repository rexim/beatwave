#ifndef NESTEDGROUP_HPP_
#define NESTEDGROUP_HPP_

#include <utility>
#include <core/animatedtuple.hpp>

template <typename ...Tp>
class NestedGroup
{
public:
    NestedGroup(Tp&&... members):
        m_members(std::move(members)...)
    {}

    void tick(int32_t deltaTime)
    {
        iterateTick<0, Tp...>(m_members, deltaTime);
    }

    void render(sf::RenderTarget *renderTarget) const
    {
        iterateRender<0, Tp...>(m_members, renderTarget);
    }

protected:
    std::tuple<Tp...> m_members;
};

#endif  // NESTEDGROUP_HPP_
