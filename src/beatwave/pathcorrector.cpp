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
    wave(PATH_CORRECTOR_RADIUS, position, PATH_CORRECTOR_COLOR),
    destroyed(false)
{
    const int32_t WAVE_PROPAGATION = 4000;
    const int32_t WAVE_PAUSE = 2000;

    using namespace dsl;

    wave.animate<EmptyCircle::Radius>(
        forever(begin(from(PATH_CORRECTOR_RADIUS).to(50.0f).during(WAVE_PROPAGATION))
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
    }
}

void PathCorrector::render(sf::RenderTarget *renderTarget)
{
    if (!destroyed) {
        body.render(renderTarget);
        wave.render(renderTarget);
    }
}

void PathCorrector::hit(Player *player)
{
    if (!destroyed) {
        const auto bodyPosition = body.value<FilledCircle::Position>();
        const auto bodyRadius = body.value<FilledCircle::Radius>();

        if (player->intersectsCircle(bodyPosition, bodyRadius)) {
            player->correctPosition(bodyPosition);
            destroyed = true;
        }
    }
}

bool PathCorrector::isDestroyed() const
{
    return destroyed;
}
