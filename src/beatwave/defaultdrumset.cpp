#include <beatwave/defaultdrumset.hpp>
#include <beatwave/drumsetexception.hpp>

DefaultDrumSet::DefaultDrumSet()
{
    if (!m_kickBuffer.loadFromFile("data/kick.wav")) {
        throw DrumSetException("Cannot load data/kick.wav");
    }

    if (!m_snareBuffer.loadFromFile("data/snare.wav")) {
        throw DrumSetException("Cannot load data/snare.wav");
    }

    if (!m_hihatBuffer.loadFromFile("data/hihat.wav")) {
        throw DrumSetException("Cannot load data/hihat.wav");
    }

    if (!m_shamanBuffer.loadFromFile("data/shaman.wav")) {
        throw DrumSetException("Cannot load date/shaman.wav");
    }

    m_kickSound.setBuffer(m_kickBuffer);
    m_snareSound.setBuffer(m_snareBuffer);
    m_hihatSound.setBuffer(m_hihatBuffer);
    m_shamanSound.setBuffer(m_shamanBuffer);
}

void DefaultDrumSet::kick()
{
    m_kickSound.play();
}

void DefaultDrumSet::snare()
{
    m_snareSound.play();
}

void DefaultDrumSet::hihat()
{
    m_hihatSound.play();
}

void DefaultDrumSet::shaman()
{
    m_shamanSound.play();
}
