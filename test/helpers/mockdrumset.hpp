#ifndef MOCKDRUMSET_HPP_
#define MOCKDRUMSET_HPP_

#include <beatwave/drumset.hpp>

class MockDrumSet: public DrumSet
{
public:
    void kick() {}
    void snare() {}
    void hihat() {}
    void shaman() {}
};

#endif  // MOCKDRUMSET_HPP_
