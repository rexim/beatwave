#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <core/animations/sleep.hpp>

TEST_CASE("Sleep animation should not be finished during it's timeout", "[sleep]") {
    Sleep<int> sleep(100);

    for (int i = 0; i < 4; ++i) {
        REQUIRE ( !sleep.isFinished() );
        sleep.nextValue(25);
    }

    REQUIRE ( sleep.isFinished() );
}

TEST_CASE("Sleep animation should return the value it was reset with", "[sleep]") {
    Sleep<int> sleep(100);

    REQUIRE ( sleep.getCurrentValue() == int() );

    sleep.reset(42);

    for (int i = 0; i < 4; ++i) {
        REQUIRE ( sleep.nextValue(25) == 42 );
    }

    REQUIRE ( sleep.getCurrentValue() == 42 );
}

TEST_CASE("Sleep animation should appear finished with negative timeout", "[sleep]") {
    Sleep<int> sleep(-100);

    REQUIRE ( sleep.isFinished() );
}
