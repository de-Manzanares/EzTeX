#include "Lexer.h"
#include "Token.h"
#include <iostream>
#include <string>
#include <vector>

class EzTeX {
 public:
  void run_file(std::string const &file_name);
  void run_repl();
  void run(std::string const &str);

 private:
  bool error = false;
};

int main(const int argc, const char *argv[]) {
  EzTeX eztex;
  if (argc > 2) {
    std::cout << "To convert a file : eztex [file]\n";
    std::cout << "To enter REPL mode: eztex \n";
  } else if (argc > 1) {
    eztex.run_file(argv[1]);
  } else {
    eztex.run_repl();
  }
  return EXIT_SUCCESS;
}

void EzTeX::run_file(std::string const &file_name) {
  std::cout << file_name << '\n';
}

void EzTeX::run_repl() {
  std::string str;
  std::cout << "eztex> ";
  while (std::getline(std::cin, str)) {
    run(str);
    std::cout << "eztex> ";
    error = false;
  }
}

void EzTeX::run(std::string const &str) {
  for (Lexer lexer(str); auto const &token : lexer.lex_tokens()) {
    std::cout << token.to_string() << '\n';
  }
}
