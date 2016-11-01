#include <SFML/System.hpp>
#include <core/dsl.hpp>
#include <core/util.hpp>

#include <beatwave/pathcorrector.hpp>

PathCorrector::PathCorrector(const sf::Vector2f &position):
    body(10.0f, position, sf::Color(255, 100, 100)),
    wave(10.0f, position, sf::Color(255, 100, 100))
{
    using namespace dsl;
    wave.animate<EmptyCircle::Radius>(forever(from(10.0f).to(30.0f).during(2000)));
    wave.animate<EmptyCircle::Color>(
        forever(map<FloatColor, sf::Color>(
                    from(uncompressColor(sf::Color(255, 100, 100)))
                    .to(uncompressColor(sf::Color::Black))
                    .during(2000),
                    compressColor, uncompressColor)));
}

void PathCorrector::tick(int32_t deltaTime)
{
    body.tick(deltaTime);
    wave.tick(deltaTime);
}

void PathCorrector::render(sf::RenderTarget *renderTarget)
{
    body.render(renderTarget);
    wave.render(renderTarget);
}
