#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <core/animated.hpp>

TEST_CASE("Animating object with nullptr should not crash the app", "[animated]") {
    Animated<int> x(10);
    x.animate(nullptr);
}
