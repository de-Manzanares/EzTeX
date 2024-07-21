#include "Lexer.h"
#include "Token.h"
#include "Translator.h"

#include <fstream>
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

/**
 * Syntax-directed translation scheme
 *       start -> list myEOF
 *        list -> (symbol | content) list | empty
 *      symbol -> { print ('\'symbol) }
 *     content -> { print (content) }
 */
int main(const int argc, const char *argv[]) {
  if (argc > 2) {
    std::cout << "To convert a file : ./hatchling [file]\n";
    std::cout << "To enter REPL mode: ./hatchling \n";
  } else if (argc > 1) {
    try {
      EzTeX eztex;
      eztex.run_file(argv[1]);
    } catch (std::runtime_error &e) {
    }
  } else {
    while (true) {
      try {
        EzTeX eztex;
        eztex.run_repl();
      } catch (std::runtime_error &e) {
      }
    }
  }
  return EXIT_SUCCESS;
}

void EzTeX::run_file(std::string const &file_name) {
  std::ifstream ifstream(file_name);
  try {
    if (!ifstream.is_open()) {
      throw std::runtime_error(file_name + " not found\n");
    }
  } catch ([[maybe_unused]] std::runtime_error &e) {
    std::cerr << "Failed to open file: " << e.what() << '\n';
  }
  std::vector<std::string> strings{};
  std::string str;
  while (std::getline(ifstream, str)) {
    strings.push_back(str);
  }
  Lexer lexer;
  Translator translator;
  translator.translate(lexer.lex_tokens(strings));
}

void EzTeX::run_repl() {
  std::string str;
  std::cout << "eztex> ";
  while (std::getline(std::cin, str)) {
    run(str);
    std::cout << "\neztex> ";
    error = false;
  }
}

void EzTeX::run(std::string const &str) {
  Lexer lexer(str);
  Translator translator(lexer.lex_tokens());
  translator.translate();
}
