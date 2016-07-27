#include <SFML/Graphics/Color.hpp>
#include "util.hpp"

namespace sf {
Color operator*(const Color &color, float f)
{
  return sf::Color(color.r * f,
                   color.g * f,
                   color.b * f);
}
}
