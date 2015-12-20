#ifndef TRANSITION_HPP_
#define TRANSITION_HPP_

template <typename State>
class Transition
{
public:
    virtual ~Transition() = default;
    virtual State nextState(const sf::Int32 deltaTime) = 0;
    virtual bool isFinished() const = 0;
};

#endif  // TRANSITION_HPP_
