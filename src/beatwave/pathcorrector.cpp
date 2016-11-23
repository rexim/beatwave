#include <SFML/System.hpp>
#include <core/dsl.hpp>
#include <core/util.hpp>

#include <beatwave/player.hpp>
#include <beatwave/pathcorrector.hpp>

namespace {
    const sf::Color PATH_CORRECTOR_COLOR(100, 255, 100, 255);
    const float PATH_CORRECTOR_RADIUS = 5.0f;
}

PathCorrector::PathCorrector(const sf::Vector2f &position):
    body(PATH_CORRECTOR_RADIUS, position, PATH_CORRECTOR_COLOR),
    wave(PATH_CORRECTOR_RADIUS, position, PATH_CORRECTOR_COLOR, 2.0f),
    destroyWave(0.0, position, sf::Color::Transparent, 10.0f),
    destroyed(false)
{
    const int32_t WAVE_PROPAGATION = 2000;
    const int32_t WAVE_PAUSE = 2000;

    using namespace dsl;

    wave.animate<EmptyCircle::Radius>(
        forever(begin(from(PATH_CORRECTOR_RADIUS).to(50.0f).during(WAVE_PROPAGATION))
                .then(sleep<float>(WAVE_PAUSE))
                .end()));

    wave.animate<EmptyCircle::Thickness>(
        forever(begin(from(3.0f).to(0.0f).during(WAVE_PROPAGATION))
                .then(sleep<float>(WAVE_PAUSE))
                .end()));

    wave.animate<EmptyCircle::Color>(
        forever(begin(map<FloatColor, sf::Color>(from(uncompressColor(PATH_CORRECTOR_COLOR))
                                                 .to(uncompressColor(sf::Color(100, 255, 100, 0)))
                                                 .during(WAVE_PROPAGATION),
                                                 compressColor, uncompressColor))
                .then(sleep<sf::Color>(WAVE_PAUSE))
                .end()));
}

void PathCorrector::tick(int32_t deltaTime)
{
    if (!destroyed) {
        body.tick(deltaTime);
        wave.tick(deltaTime);
    } else {
        destroyWave.tick(deltaTime);
    }
}

void PathCorrector::render(sf::RenderTarget *renderTarget)
{
    if (!destroyed) {
        body.render(renderTarget);
        wave.render(renderTarget);
    } else {
        destroyWave.render(renderTarget);
    }
}

void PathCorrector::hit(Player *player)
{
    if (!destroyed) {
        const auto bodyPosition = body.value<FilledCircle::Position>();
        const auto bodyRadius = body.value<FilledCircle::Radius>();

        if (player->intersectsCircle(bodyPosition, bodyRadius)) {
            player->correctPosition(bodyPosition);
            destroy();
        }
    }
}

void PathCorrector::destroy()
{
    using namespace dsl;

    destroyed = true;
    destroyWave.animate<EmptyCircle::Color>(
        map<FloatColor, sf::Color>(from(uncompressColor(sf::Color(100, 255, 100, 255)))
                                   .to(uncompressColor(sf::Color(100, 255, 100, 0)))
                                   .during(300),
                                   compressColor, uncompressColor));

    destroyWave.animate<EmptyCircle::Thickness>(from(10.0f).to(0.0f).during(300));

    destroyWave.animate<EmptyCircle::Radius>(from(0.0f).to(500.0f).during(300));

}

bool PathCorrector::isDestroyed() const
{
    return destroyed;
}
