#include <beatwave/drumsetexception.hpp>

DrumSetException::DrumSetException(const char *message):
    m_message(message)
{}

const char *DrumSetException::what() const noexcept
{
    return m_message;
}
