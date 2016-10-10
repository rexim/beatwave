#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <core/animated.hpp>
#include <core/set.hpp>
#include <core/dsl.hpp>

TEST_CASE("Set animation sets value of animated object", "[set]") {
    Animated<int> x(10);
    REQUIRE( x.value() == 10 );

    x.animate(dsl::set(20));
    REQUIRE( x.value() == 20 );
}
