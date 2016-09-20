#include <SFML/Audio/Sound.hpp>
#include <beatwave/player.hpp>
#include <beatwave/config.hpp>
#include <core/util.hpp>
#include <core/dsl.hpp>

Player::Player(const sf::Vector2f &position):
    m_circle(config::PLAYER_INIT_RADIUS,
             position,
             config::PLAYER_INIT_COLOR),
    m_splat(20),
    m_dead(false)
{}

void Player::tick(int32_t deltaTime)
{
    m_circle.tick(deltaTime);
    m_splat.tick(deltaTime);
}

void Player::render(sf::RenderTarget *renderTarget) const
{
    m_circle.render(renderTarget);
    m_splat.render(renderTarget);
}

void Player::step(const sf::Color &flashColor,
                  const sf::Vector2f direction,
                  sf::Sound *sound)
{
    using namespace dsl;

    if (!m_dead) {
        m_circle.animate<Circle::Color>(from(flashColor)
                                        .to(sf::Color::White)
                                        .during(config::COLOR_TIME));

        m_circle.animate<Circle::Position>(from(m_circle.value<Circle::Position>())
                                           .by(direction)
                                           .during(config::MOVE_TIME));

        sound->play();
    } else {
        reset();
    }
}

void Player::centerView(sf::RenderTarget *renderTarget) const
{
    renderTarget->setView(sf::View(m_circle.value<Circle::Position>(), renderTarget->getView().getSize()));
}

void Player::reset()
{
    using namespace dsl;

    m_circle.animate<Circle::Position>(set(config::PLAYER_INIT_POSITION));
    m_circle.animate<Circle::Color>(set(config::PLAYER_INIT_COLOR));
    m_circle.animate<Circle::Radius>(set(config::PLAYER_INIT_RADIUS));
    m_dead = false;
}

void Player::kill()
{
    if (!m_dead) {
        m_circle.stop();
        m_dead = true;

        using namespace dsl;

        const int COLLAPSE_TIME = 100;
        m_circle.animate<Circle::Radius>(from(config::PLAYER_INIT_RADIUS).to(0.0f).during(COLLAPSE_TIME));
        m_splat.splat(m_circle.value<Circle::Position>(), 500.0);
    }
}

bool Player::fits(const sf::FloatRect &rect) const
{
    const auto center = m_circle.value<Circle::Position>();

    const std::array<float, 4> ds = {
        std::abs(rect.top - center.y),
        std::abs(rect.top + rect.height - 1 - center.y),
        std::abs(rect.left - center.x),
        std::abs(rect.left + rect.width - 1 - center.x)
    };

    return rect.contains(center) && std::all_of(ds.begin(), ds.end(), [this](float d) {
            return m_circle.value<Circle::Radius>() < d;
    });
}

bool Player::isDead() const
{
    return m_dead;
}
