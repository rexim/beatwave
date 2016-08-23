#ifndef CONFIG_HPP_
#define CONFIG_HPP_

namespace config {
    const sf::Vector2f PLAYER_INIT_POSITION(200.0f, 200.0f);
    const float PLAYER_INIT_RADIUS = 50.0f;
    const sf::Color PLAYER_INIT_COLOR = sf::Color::White;

    const float PLAYER_MOVE_DISTANCE = 250.0f;

    const sf::Int32 MOVE_TIME = 500;
    const sf::Int32 COLOR_TIME = 700;

    const sf::Color WALL_COLOR = sf::Color(0, 130, 140);
}

#endif  // CONFIG_HPP_
