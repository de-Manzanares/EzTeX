#ifndef INCLUDE_TRANSLATOR_H_
#define INCLUDE_TRANSLATOR_H_

#include "Token.h"
#include <utility>
#include <vector>

class Token;

class Translator {
 public:
  explicit Translator(std::vector<Token> tokens = std::vector<Token>{})
      : _tokens(std::move(tokens)) {}
  void translate();
  void translate(std::vector<Token> tokens);

 private:
  value _current{}; ///< current token
  Token _lookahead; ///< predictive parser -- no backtracking
  std::vector<Token> _tokens;
  std::vector<int> _l_paren;
  std::vector<int> _r_paren;
  std::vector<int> _fractions;
  std::vector<int> _skip;
  void find_l_paren();
  void find_r_paren();
  void find_fractions();
};

#endif // INCLUDE_TRANSLATOR_H_
