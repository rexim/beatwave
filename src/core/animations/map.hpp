#ifndef CORE_ANIMATIONS_MAP_HPP_
#define CORE_ANIMATIONS_MAP_HPP_

#include <functional>
#include <core/animation.hpp>
#include <core/animations/nil.hpp>

template <typename InputValue, typename OutputValue>
class Map: public Animation<OutputValue>
{
public:
    using Mapper = std::function<OutputValue(const InputValue&)>;
    using ReversedMapper = std::function<InputValue(const OutputValue&)>;

    Map(AnimationPtr<InputValue> &&animation, Mapper mapper, ReversedMapper reversedMapper):
        m_animation(animation ? std::move(animation) : AnimationPtr<InputValue>(new Nil<InputValue>())),
        m_mapper(mapper),
        m_reversedMapper(reversedMapper)
    {}

    virtual OutputValue nextValue(const int32_t deltaTime) override
    {
        return m_mapper(m_animation->nextValue(deltaTime));
    }

    virtual OutputValue getCurrentValue() const override
    {
        return m_mapper(m_animation->getCurrentValue());
    }

    virtual bool isFinished() const override
    {
        return m_animation->isFinished();
    }

    virtual void reset(const OutputValue &value) override
    {
        m_animation->reset(m_reversedMapper(value));
    }

private:
    AnimationPtr<InputValue> m_animation;
    Mapper m_mapper;
    ReversedMapper m_reversedMapper;
};

#endif  // CORE_ANIMATIONS_MAP_HPP_
