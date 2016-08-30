#ifndef SPLAT_HPP_
#define SPLAT_HPP_

#include <vector>
#include <beatwave/drop.hpp>

class Splat
{
public:
    Splat(size_t dropCount);

private:
    std::vector<Drop> m_drops;
};

#endif  // SPLAT_HPP_
