#ifndef CORE_CAPTURES_HPP_
#define CORE_CAPTURES_HPP_

#include <deque>
#include <string>
#include <SFML/System.hpp>

using Capture = std::pair<int, int32_t>;

void dumpCaptureInfo(const std::deque<Capture> &captures,
                     const std::string &capturesFileName);

void loadCaptureInfo(std::deque<Capture> &captures,
                     const std::string &capturesFileName);

#endif  // CORE_CAPTURES_HPP_
