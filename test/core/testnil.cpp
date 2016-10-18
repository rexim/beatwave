#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <core/animations/nil.hpp>

TEST_CASE("Nil animation should always return default value", "[nil]") {
    auto nil = Nil<int>();
    REQUIRE ( int() == nil.nextValue(38945) );
    REQUIRE ( int() == nil.getCurrentValue() );
}

TEST_CASE("Nil animation should be always finished and ignore reset", "[nil]") {
    auto nil = Nil<int>();
    REQUIRE ( nil.isFinished() );
    nil.reset(3948);
    REQUIRE ( nil.isFinished() );
}
