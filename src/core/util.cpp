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
