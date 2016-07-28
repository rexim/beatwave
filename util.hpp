#ifndef UTIL_HPP_
#define UTIL_HPP_

#if !(defined (SFML_VERSION_MAJOR) && defined (SFML_VERSION_MINOR))
#error "Unsupported version of SFML is used. Please use SFML 2.0+."
#endif

#include <SFML/Config.hpp>

namespace sf {
    class Color;

    Color operator*(const Color &color, float f);
#if SFML_VERSION_MAJOR == 2 && SFML_VERSION_MINOR < 2
    Color operator-(const Color& left, const Color& right);
#endif

}  // namespace sf


#endif  // UTIL_HPP_
