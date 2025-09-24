#pragma once

#include <iostream>
#include <string_view>

void report(int line, std::string_view where, std::string_view message) {
  std::cerr << "[line " << line << "] Error" << where << ": " << message
            << "\n";
  bool hadError = true;
}
void error(int line, std::string_view message) { report(line, "", message); }
