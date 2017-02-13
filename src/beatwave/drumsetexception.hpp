#ifndef DRUMSETEXCEPTION_HPP_
#define DRUMSETEXCEPTION_HPP_

#include <exception>

class DrumSetException: public std::exception
{
public:
    DrumSetException(const char *message);

    virtual const char *what() const noexcept override;

private:
    const char *m_message;
};

#endif  // DRUMSETEXCEPTION_HPP_
