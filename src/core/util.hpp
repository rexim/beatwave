#ifndef CORE_UTIL_HPP_
#define CORE_UTIL_HPP_

#if !(defined (SFML_VERSION_MAJOR) && defined (SFML_VERSION_MINOR))
#error "Unsupported version of SFML is used. Please use SFML 2.0+."
#endif

#include <cmath>

#include <SFML/Config.hpp>

#include <core/floatcolor.hpp>

namespace sf {
    class Color;

    Color operator*(const Color &color, float f);
#if SFML_VERSION_MAJOR == 2 && SFML_VERSION_MINOR < 2
    Color operator-(const Color& left, const Color& right);
#endif

}  // namespace sf

FloatColor uncompressColor(const sf::Color &color);
sf::Color compressColor(const FloatColor &color);

#endif  // CORE_UTIL_HPP_
