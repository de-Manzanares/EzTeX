#include "Lexer.h"

#include <stdexcept>
#include <string>
#include <vector>

Lexer::Lexer(std::string str) : _str(std::move(str)) {}

std::unordered_map<std::string, Token_Type> Lexer::keywords = {
    // trig
    {"sin", Token_Type::SIN},
    {"cos", Token_Type::COS},
    {"tan", Token_Type::TAN},
    {"sec", Token_Type::SEC},
    {"csc", Token_Type::CSC},
    {"cot", Token_Type::COT},
    {"sinh", Token_Type::SINH},
    {"cosh", Token_Type::COSH},
    {"tanh", Token_Type::TANH},
    {"alpha", Token_Type::ALPHA_LOWER},
    {"beta", Token_Type::BETA_LOWER},
    {"Gamma", Token_Type::GAMMA_UPPER},
    {"gamma", Token_Type::GAMMA_LOWER},
    {"Delta", Token_Type::DELTA_UPPER},
    {"delta", Token_Type::DELTA_LOWER},
    {"epsilon", Token_Type::EPSILON_LOWER},
    {"zeta", Token_Type::ZETA_LOWER},
    {"eta", Token_Type::ETA_LOWER},
    {"theta", Token_Type::THETA_LOWER},
    {"iota", Token_Type::IOTA_LOWER},
    {"kappa", Token_Type::KAPPA_LOWER},
    {"Lambda", Token_Type::LAMBDA_UPPER},
    {"lambda", Token_Type::LAMBDA_LOWER},
    {"mu", Token_Type::MU_LOWER},
    {"nu", Token_Type::NU_LOWER},
    {"Xi", Token_Type::XI_UPPER},
    {"xi", Token_Type::XI_LOWER},
    {"Pi", Token_Type::PI_UPPER},
    {"pi", Token_Type::PI_LOWER},
    {"rho", Token_Type::RHO_LOWER},
    {"Sigma", Token_Type::SIGMA_UPPER},
    {"sigma", Token_Type::SIGMA_LOWER},
    {"tau", Token_Type::TAU_LOWER},
    {"Upsilon", Token_Type::UPSILON_UPPER},
    {"upsilon", Token_Type::UPSILON_LOWER},
    {"Phi", Token_Type::PHI_UPPER},
    {"phi", Token_Type::PHI_LOWER},
    {"chi", Token_Type::CHI_LOWER},
    {"Psi", Token_Type::PSI_UPPER},
    {"psi", Token_Type::PSI_LOWER},
    {"Omega", Token_Type::OMEGA_UPPER},
    {"omega", Token_Type::OMEGA_LOWER},
};

std::vector<Token> Lexer::lex_tokens(std::vector<std::string> strings) {
  std::vector<std::vector<Token>> tmp;
  for (auto const &str : strings) {
    tmp.push_back(lex_tokens(str));
    // the way it is set up now, at the end of each string an ezEOF token is
    // added to the token list. Fine, however, that wont' work if we are trying
    // to parse more than one string. So, ... pop_back() :-)
    // not the best solution, but it'll work for now
    if (str != strings.back()) {
      tmp.back().pop_back();
    }
  }
  _tokens.clear();
  for (auto const &v : tmp) {
    for (auto const &t : v) {
      _tokens.push_back(t);
    }
  }
  return _tokens;
}

std::vector<Token> Lexer::lex_tokens(std::string str) {
  _start = _current = 0;
  _str = std::move(str);
  _tokens.clear();
  return lex_tokens();
}

std::vector<Token> Lexer::lex_tokens() {
  while (!is_at_end()) {
    _start = _current; // move to start of next lexeme
    lex_token();
  }
  // final EOF token
  _tokens.emplace_back(Token_Type::ezEOF, "", "", _line);
  return _tokens;
}

void Lexer::lex_token() {
  using tt = Token_Type;
  switch (unsigned char const ch = _str[_current++]) {
  case ' ': // ignore whitespaces
  case '\r':
  case '\t':
    break;
  case '\n':
    _line++;
    break;
    // single character tokens
  case '(':
    push_token(tt::LEFT_PAREN);
    break;
  case ')':
    push_token(tt::RIGHT_PAREN);
    break;
  case '{':
    push_token(tt::LEFT_BRACE);
    break;
  case '}':
    push_token(tt::RIGHT_BRACE);
    break;
  case '/':
    push_token(tt::SLASH);
    break;
  case '^':
    push_token(tt::CARET);
    break;
  case '_':
    push_token(tt::USCORE);
    break;

    // one or two character tokens
    // case '<':
    // case '>':

  default: {
    if (std::isalnum(ch) || ch == '<' || ch == '>') {
      keyword_or_content();
    } else {
      push_token(tt::CONTENT);
    }
  }
  }
}

bool Lexer::is_at_end() const { return _current >= _str.length(); }

void Lexer::push_token(Token_Type token, std::string const &content) {
  _tokens.emplace_back(token, _str.substr(_start, _current - _start), content,
                       _line);
}

void Lexer::keyword_or_content() {
  while (std::isalnum(_str[_current])) {
    ++_current;
  }
  if (const std::string content = _str.substr(_start, _current - _start);
      !keywords.contains(content)) {
    push_token(Token_Type::CONTENT);
  } else {
    push_token(keywords[content], content);
  }
}
