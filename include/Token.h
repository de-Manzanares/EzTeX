#ifndef INCLUDE_TOKEN_H_
#define INCLUDE_TOKEN_H_
#include <string>

using value = uint64_t;

enum class Token_Type {
  NILL,
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
  ALPHA_LOWER,
  BETA_LOWER,
  GAMMA_UPPER,
  GAMMA_LOWER,
  DELTA_UPPER,
  DELTA_LOWER,
  EPSILON_LOWER,
  ZETA_LOWER,
  ETA_LOWER,
  THETA_LOWER,
  IOTA_LOWER,
  KAPPA_LOWER,
  LAMBDA_UPPER,
  LAMBDA_LOWER,
  MU_LOWER,
  NU_LOWER,
  XI_UPPER,
  XI_LOWER,
  PI_UPPER,
  PI_LOWER,
  RHO_LOWER,
  SIGMA_UPPER,
  SIGMA_LOWER,
  TAU_LOWER,
  UPSILON_UPPER,
  UPSILON_LOWER,
  PHI_UPPER,
  PHI_LOWER,
  CHI_LOWER,
  PSI_UPPER,
  PSI_LOWER,
  OMEGA_UPPER,
  OMEGA_LOWER,

  ezEOF
};

class Token {
 public:
  explicit Token(Token_Type const &token = Token_Type::NILL,
                 std::string lexeme = "", std::string content = "",
                 value line = 1);
  [[nodiscard]] std::string to_string() const;
  [[nodiscard]] Token_Type const &token_type() const { return _token_type; }
  [[nodiscard]] std::string const &lexeme() const { return _lexeme; }
  [[nodiscard]] value const &line() const { return _line; }

 private:
  Token_Type _token_type;
  std::string _lexeme;
  std::string _content;
  value _line;
};

#endif // INCLUDE_TOKEN_H_
