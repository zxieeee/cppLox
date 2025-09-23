#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <system_error>

void run(std::string_view content) {

  // For now, just print the tokens.
  for (Token token : tokens) {
    std::puts(token);
  }
}

void runPrompt() {

  for (;;) {
    std::cout << "> ";
    std::string line;
    if (!std::getline(std::cin, line))
      break;
    run(line);
  }
}

std::string readFile(std::string_view path) {
  std::string contents;
  std::ifstream file{path.data(),
                     std::ios::in | std::ios::binary | std::ios::ate};

  if (!file) {
    std::cerr << "Failed to open file " << path << ":"
              << std::system_category().message(errno) << "\n";
  }
  contents.resize(file.tellg());
  file.seekg(0, std::ios::beg);
  file.read(contents.data(), contents.size());

  return contents;
}

void runFile(std::string_view path) {
  std::string bytes = readFile(path);
  run(bytes);
}

void report(int line, std::string_view where, std::string_view message) {
  std::cerr << "[line " << line << "] Error" << where << ": " << message
            << "\n";
  bool hadError = true;
}
void error(int line, std::string_view message) { report(line, "", message); }

int main(int argc, char *argv[]) {
  if (argc > 2) {
    std::cout << "Usage: cpplox [script]";
    std::exit(64);
  } else if (argc == 2) {
    runFile(argv[1]);
  } else {
    runPrompt();
  }

  return 0;
}
