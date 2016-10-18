#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>

#include <core/animations/map.hpp>

class CountAnimation: public Animation<int>
{
public:
    CountAnimation():
        currentValue(0)
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

    virtual void reset(const int&) override
    {
        currentValue = 0;
    }

private:
    int currentValue;
};

TEST_CASE("Map::nextValue should map the value the wrapped animation", "[map]") {
    const std::array<int, 5> expected = { 0, 2, 4, 6, 8 };

    auto map = AnimationPtr<int>(
        new Map<int, int>(AnimationPtr<int>(new CountAnimation()),
                          [](const int& x) { return x * 2; },
                          [](const int& x) { return x / 2; }));

    for (int x: expected) {
        REQUIRE ( x == map->nextValue(10) );
    }
}
