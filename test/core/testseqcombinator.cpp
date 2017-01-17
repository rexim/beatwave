#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>

#include <core/animated.hpp>
#include <core/animations/seqcombinator.hpp>

#include <helpers/countanimation.hpp>

TEST_CASE("Sequence combinator should perform animations sequentially", "[seqcombinator]") {
    std::vector<AnimationPtr<int>> animations;
    animations.push_back(AnimationPtr<int>(new CountAnimation<true>(1, 2)));
    animations.push_back(AnimationPtr<int>(new CountAnimation<true>(3, 4)));

    SeqCombinator<int> seq(std::move(animations));

    REQUIRE ( seq.getCurrentValue() == 1 );
    REQUIRE ( seq.nextValue(0) == 2 );
    REQUIRE ( !seq.isFinished() );

    REQUIRE ( seq.nextValue(0) == 3 );
    REQUIRE ( seq.nextValue(0) == 4 );
    REQUIRE ( !seq.isFinished() );

    REQUIRE ( seq.nextValue(0) == 4 );
    REQUIRE ( seq.isFinished() );

    REQUIRE ( seq.getCurrentValue() == 4 );
}

TEST_CASE("Sequence combinator should not crash the app on empty sequence", "[seqcombinator]") {
    Animated<int> x(10);
    x.animate(AnimationPtr<int>(new SeqCombinator<int>(std::vector<AnimationPtr<int>>())));
}

TEST_CASE("Sequence combinator should not crash the app on null animations in the sequence", "[seqcombinator]") {
    std::vector<AnimationPtr<int>> animations;
    animations.push_back(nullptr);
    SeqCombinator<int> seq(std::move(animations));

    REQUIRE ( seq.nextValue(0) == int() );
    REQUIRE ( seq.getCurrentValue() == int() );
    REQUIRE ( seq.isFinished() );
    seq.reset(0);
}
