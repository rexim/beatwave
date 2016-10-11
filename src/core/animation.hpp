#ifndef CORE_ANIMATION_HPP_
#define CORE_ANIMATION_HPP_

#include <memory>

/// \brief The core animation interface of the framework.
///
/// All animations should implement this interface to be able to work
/// with the framework.
///
/// Any animations in the framework can be viewed as a small program,
/// that can be composed with other similar program inside of the
/// framework. An animation can be in the following states:
///
/// - `Invalid`
/// - `In Progress`
/// - `Finished`
///
/// When an animation is constructed it can be in any of the above
/// states. When reset() is invoked the animation goes either to `In
/// Progress` or `Finished` state.
///
/// When animation is finished isFinished() returns true. When the
/// animation is in `Invalid` state, the behaviour of isFinished() is
/// not defined.
///
/// \sa Animated
template <typename Value>
class Animation
{
public:
    virtual ~Animation() = default;
    virtual Value nextValue(const int32_t deltaTime) = 0;
    virtual Value getCurrentValue() const = 0;
    virtual bool isFinished() const = 0;
    virtual void reset(const Value&) = 0;
};

template <typename Value>
using AnimationPtr = std::unique_ptr<Animation<Value>>;

#endif  // CORE_ANIMATION_HPP_
