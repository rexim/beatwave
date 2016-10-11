#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>

#include <core/animated.hpp>
#include <core/animations/seqcombinator.hpp>

TEST_CASE("Sequence combinator should not crash the app on empty sequence", "[seqcombinator]") {
    Animated<int> x(10);
    x.animate(AnimationPtr<int>(new SeqCombinator<int>(std::vector<AnimationPtr<int>>())));
}
