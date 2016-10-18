#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>

#include <core/animations/map.hpp>

class CountAnimation: public Animation<int>
{
public:
    CountAnimation(int initialValue):
        currentValue(initialValue)
    {}

    virtual int nextValue(const int32_t) override
    {
        return currentValue++;
    }

    virtual int getCurrentValue() const override
    {
        return currentValue;
    }

    virtual bool isFinished() const override
    {
        return false;
    }

    virtual void reset(const int &initialValue) override
    {
        currentValue = initialValue;
    }

private:
    int currentValue;
};

AnimationPtr<int> makeCountMap(int initialValue)
{
    return AnimationPtr<int>(
        new Map<int, int>(AnimationPtr<int>(new CountAnimation(initialValue)),
                          [](const int& x) { return x * 2; },
                          [](const int& x) { return x / 2; }));
}

TEST_CASE("Map::nextValue should map the value the wrapped animation", "[map]") {
    const std::array<int, 5> expected = { 0, 2, 4, 6, 8 };
    auto map = makeCountMap(0);

    for (int x: expected) {
        REQUIRE ( x == map->nextValue(10) );
    }

    for (size_t i = 0; i < 5; ++i) {
        REQUIRE ( 10 == map->getCurrentValue() );
    }
}
