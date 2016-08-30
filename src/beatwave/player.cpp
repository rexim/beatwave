#include <beatwave/player.hpp>
#include <beatwave/config.hpp>
#include <core/util.hpp>
#include <core/dsl.hpp>

Player::Player(const sf::Vector2f &position,
               float radius,
               const sf::Color &color):
    position(position),
    radius(radius),
    color(color)
{}

void Player::tick(int32_t deltaTime)
{
    position.tick(deltaTime);
    radius.tick(deltaTime);
    color.tick(deltaTime);
}

void Player::render(sf::RenderTarget *renderTarget) const
{
    sf::CircleShape circle(radius.value());
    circle.setFillColor(color.value());
    circle.setPosition(position.value() - sf::Vector2f(radius.value(), radius.value()));

    renderTarget->draw(circle);
}

void Player::step(const sf::Color &flashColor,
                  const sf::Vector2f direction)
{
    using namespace dsl;

    color.animate(from(flashColor)
                  .to(sf::Color::White)
                  .during(config::COLOR_TIME));
    position.animate(from(position.value())
                     .by(direction)
                     .during(config::MOVE_TIME));
}

void Player::centerView(sf::RenderTarget *renderTarget) const
{
    renderTarget->setView(sf::View(position.value(), renderTarget->getView().getSize()));
}

void Player::reset()
{
    using namespace dsl;

    position.animate(from(position.value()).to(config::PLAYER_INIT_POSITION).during(config::MOVE_TIME));
    color.animate(from(color.value()).to(config::PLAYER_INIT_COLOR).during(config::MOVE_TIME));
    radius.animate(from(radius.value()).to(config::PLAYER_INIT_RADIUS).during(config::MOVE_TIME));
}

void Player::kill()
{
    using namespace dsl;

    const int COLLAPSE_TIME = 100;
    radius.animate(from(config::PLAYER_INIT_RADIUS).to(0.0f).during(COLLAPSE_TIME));
}
