#pragma once

#include <string>
#include <sstream>
#include <istream>

inline std::string ReadTextStream(std::istream& src) {
  std::stringstream s;
  s << src.rdbuf();
  return s.str();
}
