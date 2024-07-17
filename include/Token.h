#ifndef INCLUDE_TOKEN_H_
#define INCLUDE_TOKEN_H_
#include <string>

using value = uint64_t;

enum class Token_Type {
  // single character tokens
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  STAR,
  SLASH,
  CARET,
  USCORE,

  // literals
  CONTENT,

  // keywords
  // symbols
  NEQ,
  LESS_EQUAL,
  GREATER_EQUAL,
  PLUS_MINUS,
  MINUS_PLUS,
  SQRT,
  // trig
  SIN,
  COS,
  TAN,
  SEC,
  CSC,
  COT,
  SINH,
  COSH,
  TANH,
  // greek alphabet
  SIGMA_LOWER,
  SIGMA_UPPER,

  ezEOF
};

class Token {
 public:
  Token(Token_Type const &token, std::string lexeme, std::string content,
        value line);
  [[nodiscard]] std::string to_string() const;
  [[nodiscard]] Token_Type const &token_type() const { return _token_type; }

 private:
  Token_Type _token_type;
  std::string _lexeme;
  std::string _content;
  value _line{};
};

#endif // INCLUDE_TOKEN_H_
