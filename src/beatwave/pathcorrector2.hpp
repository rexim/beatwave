#ifndef PATHCORRECTOR2_HPP_
#define PATHCORRECTOR2_HPP_

#include <core/util.hpp>
#include <core/floatcolor.hpp>
#include <core/dsl.hpp>
#include <core/nestedgroup.hpp>
#include <beatwave/filledcircle.hpp>
#include <beatwave/emptycircle.hpp>

namespace {
    const sf::Color PATH_CORRECTOR_COLOR(100, 255, 100, 255);
    const float PATH_CORRECTOR_RADIUS = 5.0f;
}

class PathCorrector2: public NestedGroup<FilledCircle, // core
                                         EmptyCircle>  // wave
{
public:
    PathCorrector2(const sf::Vector2f &position):
        NestedGroup(FilledCircle(PATH_CORRECTOR_RADIUS, position, PATH_CORRECTOR_COLOR),
                    EmptyCircle(PATH_CORRECTOR_RADIUS, position, PATH_CORRECTOR_COLOR, 2.0f)),
        m_core(std::get<0>(m_members)),
        m_wave(std::get<1>(m_members)),
        m_destroyed(false)
    {
        const int32_t WAVE_PROPAGATION = 2000;
        const int32_t WAVE_PAUSE = 2000;

        using namespace dsl;

        m_wave.animate<EmptyCircle::Radius>(
            forever(begin(from(PATH_CORRECTOR_RADIUS).to(50.0f).during(WAVE_PROPAGATION))
                    .then(sleep<float>(WAVE_PAUSE))
                    .end()));

        m_wave.animate<EmptyCircle::Thickness>(
            forever(begin(from(3.0f).to(0.0f).during(WAVE_PROPAGATION))
                    .then(sleep<float>(WAVE_PAUSE))
                    .end()));

        m_wave.animate<EmptyCircle::Color>(
            forever(begin(map<FloatColor, sf::Color>(from(uncompressColor(PATH_CORRECTOR_COLOR))
                                                     .to(uncompressColor(sf::Color(100, 255, 100, 0)))
                                                     .during(WAVE_PROPAGATION),
                                                     compressColor, uncompressColor))
                    .then(sleep<sf::Color>(WAVE_PAUSE))
                    .end()));
    }

    void hit(Player *player)
    {
        if (!m_destroyed) {
            const auto corePosition = m_core.value<FilledCircle::Position>();
            const auto coreRadius = m_core.value<FilledCircle::Radius>();


            if (player->intersectsCircle(corePosition, coreRadius)) {
                player->correctPosition(corePosition);
                destroy();
            }
        }
    }

    bool isDestroyed() const
    {
        return m_destroyed;
    }

private:
    void destroy()
    {
        using namespace dsl;

        m_destroyed = true;

        m_core.animate<FilledCircle::Radius>(set(0.0f));
        m_wave.animate<EmptyCircle::Color>(
            map<FloatColor, sf::Color>(from(uncompressColor(sf::Color(100, 255, 100, 255)))
                                       .to(uncompressColor(sf::Color(100, 255, 100, 0)))
                                       .during(300),
                                       compressColor, uncompressColor));

        m_wave.animate<EmptyCircle::Thickness>(from(10.0f).to(0.0f).during(300));
        m_wave.animate<EmptyCircle::Radius>(from(0.0f).to(500.0f).during(300));
    }

private:
    FilledCircle &m_core;
    EmptyCircle &m_wave;
    bool m_destroyed;
};

#endif  // PATHCORRECTOR2_HPP_
