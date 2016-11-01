#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <helpers/countanimation.hpp>
#include <core/animations/repeat.hpp>

TEST_CASE("Repeat combinator should repeat underlying animation n times", "[repeat]") {
    Repeat<int> repeat(2, AnimationPtr<int>(new CountAnimation<true>(1, 2)));

    REQUIRE ( repeat.getCurrentValue() == 1 );
    REQUIRE ( repeat.nextValue(0)      == 2 );
    REQUIRE ( !repeat.isFinished() );

    REQUIRE ( repeat.nextValue(0) == 1 );
    REQUIRE ( repeat.nextValue(0) == 2 );
    REQUIRE ( !repeat.isFinished() );

    REQUIRE ( repeat.nextValue(0) == 2 );
    REQUIRE ( repeat.isFinished() );

    REQUIRE ( repeat.getCurrentValue() == 2 );

    repeat.reset(10);

    REQUIRE ( repeat.getCurrentValue() == 1 );
    REQUIRE ( !repeat.isFinished() );
}
