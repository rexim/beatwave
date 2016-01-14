#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <memory>

template <typename State>
class Animation
{
public:
    virtual ~Animation() = default;
    virtual State nextState(const sf::Int32 deltaTime) = 0;
    virtual State getCurrentState() const = 0;
    virtual bool isFinished() const = 0;
};

template <typename T>
using AnimationPtr = std::unique_ptr<Animation<T>>;

#endif  // ANIMATION_HPP_
