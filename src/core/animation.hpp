#ifndef CORE_ANIMATION_HPP_
#define CORE_ANIMATION_HPP_

#include <memory>

/// \brief Core interface for animations
///
/// %Animation is an object that describes how value changes through
/// the time. %Animation assumes the following workflow:
///
/// \code{.cpp}
/// const int initialValue = 0;
/// const int32_t deltaTime = 10;
///
///
/// // We created Animation object somehow. After construction Animation
/// // can be in Invalid state and shouldn't be used util reset.
/// Animation<int> animation = ...;
///
///
/// // We reset animation with preferable initial value. It's up to Animation
/// // to interpret that initialState. It can be even ignored.
/// animation.reset(initialValue);
/// std::cout << animation.getCurrentValue() << std::endl;
///
///
/// // Until the Animation is finished...
/// while (!animation.isFinished()) {
///     // ... we calculate it's next value after deltaTime milliseconds
///     // and print it
///     std::cout << animation.nextValue(deltaTime) << std::endl;
/// }
/// \endcode
///
/// %Animation can be in the following states:
///
/// - `Invalid`
/// - `In Progress`
/// - `Finished`
///
/// When %Animation is constructed it can be in any of the above
/// states. When reset() is invoked %Animation goes either to `In
/// Progress` or `Finished` state.
///
/// This is just assumed workflow with the object, that is good to
/// keep in mind while developing your own animation. It's not
/// supposed to be used like that by the user of the framework.
///
/// **Animations should be always assigned to Animated object, which
/// takes care of the %Animation workflow and lifetime in a manner
/// described above.**
///
/// \sa Animated
template <typename Value>
class Animation
{
public:
    virtual ~Animation() = default;

    /// \brief Calculates next value of the animation after some delta time
    ///
    /// When %Animation is in `Invalid` state the behaviour of
    /// nextValue() is not defined
    ///
    /// When %Animation is `Finished` nextValue() should return the
    /// final value of the animation without changing the state of
    /// %Animation.
    ///
    /// \param deltaTime
    virtual Value nextValue(const int32_t deltaTime) = 0;

    /// \brief Get current value of the animation without changing its state
    ///
    /// When %Animation is in `Invalid` state the behaviour of
    /// getCurrentValue() is not defined
    virtual Value getCurrentValue() const = 0;

    virtual bool isFinished() const = 0;
    virtual void reset(const Value&) = 0;
};

template <typename Value>
using AnimationPtr = std::unique_ptr<Animation<Value>>;

#endif  // CORE_ANIMATION_HPP_
