#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <memory>

template <typename State>
class Animation
{
public:
    virtual ~Animation() = default;
    virtual State nextState(const int32_t deltaTime) = 0;
    virtual State getCurrentState() const = 0;
    virtual bool isFinished() const = 0;
    virtual void reset() = 0;
};

template <typename State>
using AnimationPtr = std::unique_ptr<Animation<State>>;

#endif  // ANIMATION_HPP_
