#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>

#include <core/animations/map.hpp>
#include <helpers/countanimation.hpp>

AnimationPtr<int> makeCountMap(int initialValue, int finalState)
{
    return AnimationPtr<int>(
        new Map<int, int>(AnimationPtr<int>(new CountAnimation<false>(initialValue, finalState)),
                          [](const int& x) { return x * 2; },
                          [](const int& x) { return x / 2; }));
}

TEST_CASE("Map::nextValue() and Map::getCurrentValue() should map the value the wrapped animation", "[map]") {
    const std::array<int, 5> expected = { 2, 4, 6, 8, 10 };
    auto map = makeCountMap(0, 100);

    for (int x: expected) {
        REQUIRE ( x == map->nextValue(10) );
    }

    for (size_t i = 0; i < 5; ++i) {
        REQUIRE ( 10 == map->getCurrentValue() );
    }
}

TEST_CASE("Map::isFinished() should be equal to isFinished() of the wrapped animation", "[map]") {
    auto map = makeCountMap(0, 1);
    REQUIRE ( !map->isFinished() );
    REQUIRE ( 2 == map->nextValue(10) );
    REQUIRE ( map->isFinished() );
}

TEST_CASE("Map::reset() should use ReversedMapper to reset the wrapped animation", "[map]") {
    auto map = makeCountMap(0, 10);
    map->reset(4);
    REQUIRE ( 4 == map->getCurrentValue() );
}
