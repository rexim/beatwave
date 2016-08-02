#ifndef CAPTURES_HPP_
#define CAPTURES_HPP_

#include <deque>
#include <string>
#include <SFML/System.hpp>

using Capture = std::pair<int, sf::Int32>;

void dumpCaptureInfo(const std::deque<Capture> &captures,
                     const std::string &capturesFileName);

void loadCaptureInfo(std::deque<Capture> &captures,
                     const std::string &capturesFileName);

#endif  // CAPTURES_HPP_
