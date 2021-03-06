#include <SFML/Audio/Sound.hpp>
#include <beatwave/player.hpp>
#include <beatwave/config.hpp>
#include <core/util.hpp>
#include <core/dsl.hpp>

Player::Player(const pugi::xml_node&,
               std::unique_ptr<DrumSet> &&drumSet):
    Player(sf::Vector2f(0.0f, 0.0f), std::move(drumSet))
{
    // TODO: Implement XML constructor for Player
    //
    // It should construct the player from the XML node according to
    // the XML schema `level.xsd`. It should also check if the
    // corresponding node exists.
}

Player::Player(const sf::Vector2f &position,
               std::unique_ptr<DrumSet> &&drumSet):
    m_circle(config::PLAYER_INIT_RADIUS / 2.0f,
             position,
             config::PLAYER_INIT_COLOR),
    m_splat(20),
    m_dead(false),
    m_drumSet(std::move(drumSet))
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
                  const sf::Vector2f direction)
{
    using namespace dsl;

    if (!m_dead) {
        m_circle.animate<Circle::FillColor>(
            map<FloatColor, sf::Color>(from(uncompressColor(flashColor))
                                       .to(uncompressColor(config::PLAYER_INIT_COLOR))
                                       .during(config::COLOR_TIME),
                                       compressColor, uncompressColor));

        m_circle.animate<Circle::Position>(from(m_circle.value<Circle::Position>())
                                           .by(direction)
                                           .during(config::MOVE_TIME));

        m_circle.animate<Circle::Radius>(from(config::PLAYER_INIT_RADIUS)
                                         .to(config::PLAYER_INIT_RADIUS / 2.0f)
                                         .during(config::COLOR_TIME));
    } else {
        reset();
    }
}

void Player::kickStep()
{
    step(sf::Color::Red,
         sf::Vector2f(config::PLAYER_MOVE_DISTANCE, 0.0f));
    m_drumSet->kick();
}

void Player::snareStep()
{
    step(sf::Color::Green,
         sf::Vector2f(0.0f, config::PLAYER_MOVE_DISTANCE));
    m_drumSet->snare();
}


void Player::hihatStep()
{
    step(sf::Color::Blue,
         sf::Vector2f(0.0f, -config::PLAYER_MOVE_DISTANCE));
    m_drumSet->hihat();
}

void Player::shamanStep()
{
    step(sf::Color::Yellow,
         sf::Vector2f(-config::PLAYER_MOVE_DISTANCE, 0.0f));
    m_drumSet->shaman();
}

void Player::centerView(sf::RenderTarget *renderTarget) const
{
    renderTarget->setView(sf::View(m_circle.value<Circle::Position>(), renderTarget->getView().getSize()));
}

void Player::reset()
{
    using namespace dsl;

    m_circle.animate<Circle::Position>(set(config::PLAYER_INIT_POSITION));
    m_circle.animate<Circle::FillColor>(set(config::PLAYER_INIT_COLOR));
    m_circle.animate<Circle::Radius>(set(config::PLAYER_INIT_RADIUS / 2.0f));
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

bool Player::intersectsCircle(const sf::Vector2f &center,
                              float radius)
{
    const auto playerCenter = m_circle.value<Circle::Position>();
    const auto playerRadius = m_circle.value<Circle::Radius>();

    return vectorLegnth(playerCenter - center) <= playerRadius + radius;
}


bool Player::isDead() const
{
    return m_dead;
}

void Player::correctPosition(const sf::Vector2f &position)
{
    using namespace dsl;
    m_circle.animate<Circle::Position>(set(position));
}
