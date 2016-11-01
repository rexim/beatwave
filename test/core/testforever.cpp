#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <helpers/countanimation.hpp>
#include <core/animations/forever.hpp>

AnimationPtr<int> makeForeverCount(int initialValue, int finalValue)
{
    return AnimationPtr<int>(new Forever<int>(AnimationPtr<int>(new CountAnimation<true>(initialValue, finalValue))));
}

TEST_CASE("Forever combinator should repeat underlying animation forever", "[forever]") {
    auto forever = makeForeverCount(1, 2);
    REQUIRE ( forever->getCurrentValue() == 1 );
    REQUIRE ( forever->nextValue(0) == 2 );
    REQUIRE ( forever->nextValue(0) == 1 );
    REQUIRE ( forever->nextValue(0) == 2 );
    REQUIRE ( forever->getCurrentValue() == 2 );
    REQUIRE ( !forever->isFinished() );
}
