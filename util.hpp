#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <SFML/Config.hpp>

namespace sf {
    class Color;

    Color operator*(const Color &color, float f);
#if SFML_VERSION_MAJOR == 2 && SFML_VERSION < 2
    Color operator-(const Color& left, const Color& right);
#endif

}  // namespace sf


#endif  // UTIL_HPP_
