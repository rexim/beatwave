#ifndef CORE_UTIL_HPP_
#define CORE_UTIL_HPP_

#if !(defined (SFML_VERSION_MAJOR) && defined (SFML_VERSION_MINOR))
#error "Unsupported version of SFML is used. Please use SFML 2.0+."
#endif

#include <cmath>
#include <SFML/Config.hpp>

namespace sf {
    class Color;

    Color operator*(const Color &color, float f);
#if SFML_VERSION_MAJOR == 2 && SFML_VERSION_MINOR < 2
    Color operator-(const Color& left, const Color& right);
#endif

}  // namespace sf

FloatColor uncompressColor(const sf::Color &color)
{
    // color.r = 255.0 * std::pow(image[y * w + x].r / 255.0, 2.2);
    // color.g = 255.0 * std::pow(image[y * w + x].g / 255.0, 2.2);
    // color.b = 255.0 * std::pow(image[y * w + x].b / 255.0, 2.2);

    return FloatColor(255.0 * std::pow(color.r / 255.0, 2.2),
                      255.0 * std::pow(color.g / 255.0, 2.2),
                      255.0 * std::pow(color.b / 255.0, 2.2))
}

sf::Color compressColor(const FloatColor &color)
{
    // image[y * w + x].r = 255.0 * std::pow(color.r / 255.0, 1 / 2.2);
    // image[y * w + x].g = 255.0 * std::pow(color.g / 255.0, 1 / 2.2);
    // image[y * w + x].b = 255.0 * std::pow(color.b / 255.0, 1 / 2.2);

    return sf::Color(255.0 * std::pow(color.r / 255.0, 1 / 2.2),
                     255.0 * std::pow(color.g / 255.0, 1 / 2.2),
                     255.0 * std::pow(color.b / 255.0, 1 / 2.2))
}

#endif  // CORE_UTIL_HPP_
