#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>

#include <core/animations/map.hpp>

class CountAnimation: public Animation<int>
{
public:
    CountAnimation(int initialValue, int finalValue):
        m_finalValue(finalValue),
        m_currentValue(initialValue)
    {}

    virtual int nextValue(const int32_t) override
    {
        if (!isFinished()) {
            return m_currentValue++;
        } else {
            return getCurrentValue();
        }
    }

    virtual int getCurrentValue() const override
    {
        return m_currentValue;
    }

    virtual bool isFinished() const override
    {
        return m_currentValue >= m_finalValue;
    }

    virtual void reset(const int &initialValue) override
    {
        m_currentValue = initialValue;
    }

private:
    const int m_finalValue;
    int m_currentValue;
};

AnimationPtr<int> makeCountMap(int initialValue, int finalState)
{
    return AnimationPtr<int>(
        new Map<int, int>(AnimationPtr<int>(new CountAnimation(initialValue, finalState)),
                          [](const int& x) { return x * 2; },
                          [](const int& x) { return x / 2; }));
}

TEST_CASE("Map::nextValue() and Map::getCurrentValue() should map the value the wrapped animation", "[map]") {
    const std::array<int, 5> expected = { 0, 2, 4, 6, 8 };
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
    REQUIRE ( 0 == map->nextValue(10) );
    REQUIRE ( map->isFinished() );
}
