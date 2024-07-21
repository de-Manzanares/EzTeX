#include "Translator.h"
#include <algorithm>

#include "emit.hpp"

#include <Lexer.h>

void Translator::translate(std::vector<Token> tokens) {
  _tokens = std::move(tokens);
  translate();
}

void Translator::find_l_paren() {
  for (std::size_t i = 0; i < _tokens.size(); ++i) {
    if (_tokens[i].lexeme() == "(") {
      _fractions.push_back(static_cast<int>(i));
    }
  }
}

void Translator::find_r_paren() {
  for (std::size_t i = 0; i < _tokens.size(); ++i) {
    if (_tokens[i].lexeme() == ")") {
      _fractions.push_back(static_cast<int>(i));
    }
  }
}

void Translator::find_fractions() {
  for (std::size_t i = 0; i < _tokens.size(); ++i) {
    if (_tokens[i].lexeme() == "/") {
      _fractions.push_back(static_cast<int>(i));
    }
  }
}

void Translator::translate() {
  find_l_paren();
  find_r_paren();
  find_fractions();
  _current = 0;
  _lookahead = _tokens[_current];

  if (_l_paren.empty() && _r_paren.empty() && _fractions.empty()) {
    for (auto const &token : _tokens) {
      if (Lexer::keywords.contains(token.lexeme())) {
        std::cout << "\\" + token.lexeme() << " ";
      } else {
        std::cout << token.lexeme() << " ";
      }
    }
  } else if (_l_paren.empty() && _r_paren.empty()) {
    std::vector<std::string> groups{};
    _skip.push_back(_fractions[0] - 1);
    _skip.push_back(_fractions[0]);
    _skip.push_back(_fractions[0] + 1);
    for (std::size_t i = 0; i < _tokens.size(); ++i) {
      if (std::ranges::find(_skip, i) == _skip.end()) {
        if (Lexer::keywords.contains(_tokens[i].lexeme())) {
          std::cout << "\\" + _tokens[i].lexeme() << " ";
        } else {
          std::cout << _tokens[i].lexeme() << " ";
        }
      }
      if (std::ranges::find(_fractions, i) != _fractions.end()) {
        std::cout << "\\frac{" << _tokens[i - 1].lexeme() << "}{"
                  << _tokens[i + 1].lexeme() << "}";
      }
    }
  }
}
