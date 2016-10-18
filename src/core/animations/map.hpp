#ifndef CORE_ANIMATIONS_MAP_HPP_
#define CORE_ANIMATIONS_MAP_HPP_

#include <functional>
#include <core/animation.hpp>

template <typename InputValue, typename OutputValue>
class Map: public Animation<OutputValue>
{
public:
    using Mapper = std::function<OutputValue(const InputValue&)>;
    using ReversedMapper = std::function<InputValue(const OutputValue&)>;

    Map(AnimationPtr<InputValue> &&animation, Mapper mapper, ReversedMapper reversedMapper):
        m_animation(std::move(animation)),
        m_mapper(mapper),
        m_reversedMapper(reversedMapper)
    {}

    virtual OutputValue nextValue(const int32_t deltaTime) override
    {
        if (m_animation != nullptr) {
            return m_mapper(m_animation->nextValue(deltaTime));
        } else {
            return OutputValue();
        }
    }

    virtual OutputValue getCurrentValue() const override
    {
        if (m_animation != nullptr) {
            return m_mapper(m_animation->getCurrentValue());
        } else {
            return OutputValue();
        }
    }

    virtual bool isFinished() const override
    {
        if (m_animation != nullptr) {
            return m_animation->isFinished();
        } else {
            return true;
        }
    }

    virtual void reset(const OutputValue &value) override
    {
        if (m_animation != nullptr) {
            m_animation->reset(m_reversedMapper(value));
        }
    }

private:
    AnimationPtr<InputValue> m_animation;
    Mapper m_mapper;
    ReversedMapper m_reversedMapper;
};

#endif  // CORE_ANIMATIONS_MAP_HPP_
