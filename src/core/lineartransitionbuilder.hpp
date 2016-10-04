#ifndef LINEARTRANSITIONBUILDER_HPP_
#define LINEARTRANSITIONBUILDER_HPP_

#include <core/openlineartransition.hpp>

namespace LinearTransitionBuilder {

template <typename T>
class During
{
public:
    During(const T &initialState, const T &finalState):
        m_initialState(initialState), m_finalState(finalState)
    {}

    AnimationPtr<T> during(int32_t transitionTime)
    {
        return AnimationPtr<T>(new LinearTransition<T>(m_initialState,
                                                       transitionTime,
                                                       m_finalState));
    }

private:
    const T m_initialState;
    const T m_finalState;
};

template <typename State, bool Relative>
class OpenDuring
{
public:
    OpenDuring(const State &finalState):
        m_finalState(finalState)
    {}

    AnimationPtr<State> during(int32_t transitionTime)
    {
        return AnimationPtr<State>(new OpenLinearTransition<State, Relative>(transitionTime,
                                                                             m_finalState));
    }

private:
    const State m_finalState;
};

template <typename T>
class Toby
{
public:
    Toby(const T &initialState):
        m_initialState(initialState)
    {}

    During<T> to(const T &finalState)
    {
        return During<T>(m_initialState, finalState);
    }

    During<T> by(const T &deltaState)
    {
        return During<T>(m_initialState, m_initialState + deltaState);
    }

private:
    const T m_initialState;
};

}  // namespace LinearTransitionBuilder

#endif  // LINEARTRANSITIONBUILDER_HPP_
