#include <SFML/Graphics/Color.hpp>
#include "util.hpp"

sf::Color operator*(const sf::Color &color, float f)
{
  return sf::Color(color.r * f,
                   color.g * f,
                   color.b * f);
}
