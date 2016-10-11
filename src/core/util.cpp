#include <SFML/Config.hpp>
#include <SFML/Graphics/Color.hpp>
#include <core/util.hpp>

namespace sf {

Color operator*(const Color &color, float f)
{
    return Color(color.r * f,
                 color.g * f,
                 color.b * f);
}

#if SFML_VERSION_MAJOR == 2 && SFML_VERSION_MINOR < 2
Color operator-(const Color& left, const Color& right)
{
    return Color(left.r - right.r,
                 left.g - right.g,
                 left.b - right.b);
}
#endif

}  // namespacs sf

FloatColor uncompressColor(const sf::Color &color)
{
    // color.r = 255.0 * std::pow(image[y * w + x].r / 255.0, 2.2);
    // color.g = 255.0 * std::pow(image[y * w + x].g / 255.0, 2.2);
    // color.b = 255.0 * std::pow(image[y * w + x].b / 255.0, 2.2);

    return FloatColor(255.0 * std::pow(color.r / 255.0, 2.2),
                      255.0 * std::pow(color.g / 255.0, 2.2),
                      255.0 * std::pow(color.b / 255.0, 2.2));
}

sf::Color compressColor(const FloatColor &color)
{
    // image[y * w + x].r = 255.0 * std::pow(color.r / 255.0, 1 / 2.2);
    // image[y * w + x].g = 255.0 * std::pow(color.g / 255.0, 1 / 2.2);
    // image[y * w + x].b = 255.0 * std::pow(color.b / 255.0, 1 / 2.2);

    return sf::Color(255.0 * std::pow(color.r / 255.0, 1 / 2.2),
                     255.0 * std::pow(color.g / 255.0, 1 / 2.2),
                     255.0 * std::pow(color.b / 255.0, 1 / 2.2));
}
