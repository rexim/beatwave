#ifndef CORE_ANIMATIONS_SEQCOMBINATOR_HPP_
#define CORE_ANIMATIONS_SEQCOMBINATOR_HPP_

#include <vector>
#include <initializer_list>

#include <core/animation.hpp>
#include <core/animations/nil.hpp>

template <typename Value>
class SeqCombinator: public Animation<Value>
{
public:
    SeqCombinator(std::vector<AnimationPtr<Value>> &&animations):
        m_animations(std::move(animations)),
        m_currentAnimation(0)
    {
        for (auto &animationPtr: m_animations) {
            if (!animationPtr) {
                animationPtr.reset(new Nil<Value>());
            }
        }
    }

    virtual Value nextValue(const int32_t deltaTime) override
    {
        if (m_animations.empty()) {
            return m_emptyPlaceholder;
        }

        if (!isFinished()) {
            if (!m_animations[m_currentAnimation]->isFinished()) {
                return m_animations[m_currentAnimation]->nextValue(deltaTime);
            } else {
                const Value previousValue = m_animations[m_currentAnimation]->getCurrentValue();
                m_currentAnimation++;
                if (!isFinished()) {
                    m_animations[m_currentAnimation]->reset(previousValue);
                    return m_animations[m_currentAnimation]->getCurrentValue();
                }
            }
        }

        return m_animations.back()->getCurrentValue();
    }

    virtual Value getCurrentValue() const override
    {
        if (m_animations.empty()) {
            return m_emptyPlaceholder;
        } else if (isFinished()) {
            return m_animations.back()->getCurrentValue();
        } else {
            return m_animations[m_currentAnimation]->getCurrentValue();
        }
    }

    virtual bool isFinished() const override
    {
        return m_currentAnimation >= m_animations.size();
    }

    virtual void reset(const Value &value) override
    {
        if (m_animations.empty()) {
            m_emptyPlaceholder = value;
        } else {
            m_currentAnimation = 0;
            m_animations[m_currentAnimation]->reset(value);
        }
    }

private:
    std::vector<AnimationPtr<Value>> m_animations;
    size_t m_currentAnimation;
    Value m_emptyPlaceholder;
};

#endif  // CORE_ANIMATIONS_SEQCOMBINATOR_HPP_
