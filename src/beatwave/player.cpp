#include <beatwave/player.hpp>
#include <beatwave/config.hpp>
#include <core/util.hpp>
#include <core/dsl.hpp>

Player::Player(const sf::Vector2f &position,
               float radius,
               const sf::Color &color):
    position(position),
    radius(radius),
    color(color),
    splat(20),
    dead(false)
{}

void Player::tick(int32_t deltaTime)
{
    position.tick(deltaTime);
    radius.tick(deltaTime);
    color.tick(deltaTime);
    splat.tick(deltaTime);
}

void Player::render(sf::RenderTarget *renderTarget) const
{
    sf::CircleShape circle(radius.value());
    circle.setFillColor(color.value());
    circle.setPosition(position.value() - sf::Vector2f(radius.value(), radius.value()));

    renderTarget->draw(circle);
    splat.render(renderTarget);
}

void Player::step(const sf::Color &flashColor,
                  const sf::Vector2f direction)
{
    using namespace dsl;

    if (!dead) {
        color.animate(from(flashColor)
                      .to(sf::Color::White)
                      .during(config::COLOR_TIME));
        position.animate(from(position.value())
                         .by(direction)
                         .during(config::MOVE_TIME));
    }
}

void Player::centerView(sf::RenderTarget *renderTarget) const
{
    renderTarget->setView(sf::View(position.value(), renderTarget->getView().getSize()));
}

void Player::reset()
{
    using namespace dsl;

    position.animate(set(config::PLAYER_INIT_POSITION));
    color.animate(set(config::PLAYER_INIT_COLOR));
    radius.animate(set(config::PLAYER_INIT_RADIUS));
    dead = false;
}

void Player::kill()
{
    position.stop();
    radius.stop();
    color.stop();
    dead = true;

    using namespace dsl;

    const int COLLAPSE_TIME = 100;
    radius.animate(from(config::PLAYER_INIT_RADIUS).to(0.0f).during(COLLAPSE_TIME));
    splat.splat(position.value(), 500.0);
}

bool Player::isCompletlyInsideOf(const sf::FloatRect &rect) const
{
    const auto center = position.value();

    const std::array<float, 4> ds = {
        std::abs(rect.top - center.y),
        std::abs(rect.top + rect.height - 1 - center.y),
        std::abs(rect.left - center.x),
        std::abs(rect.left + rect.width - 1 - center.x)
    };

    return rect.contains(center) && std::all_of(ds.begin(), ds.end(), [this](float d) {
            return radius.value() < d;
    });
}
