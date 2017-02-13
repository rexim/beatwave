#ifndef BEATWAVE_DEFAULTDRUMSET_HPP_
#define BEATWAVE_DEFAULTDRUMSET_HPP_

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <beatwave/drumset.hpp>

/// \brief Class that represents available drum sounds
class DefaultDrumSet: public DrumSet
{
public:
    DefaultDrumSet();

    virtual void kick() override;
    virtual void snare() override;
    virtual void hihat() override;
    virtual void shaman() override;

private:
    sf::SoundBuffer m_kickBuffer;
    sf::SoundBuffer m_snareBuffer;
    sf::SoundBuffer m_hihatBuffer;
    sf::SoundBuffer m_shamanBuffer;
    sf::Sound m_kickSound;
    sf::Sound m_snareSound;
    sf::Sound m_hihatSound;
    sf::Sound m_shamanSound;
};

#endif  // BEATWAVE_DEFAULTDRUMSET_HPP_
