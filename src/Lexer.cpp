#include "Lexer.h"

#include <stdexcept>
#include <string>
#include <vector>

Lexer::Lexer(std::string const &str) { _str = str; }

std::unordered_map<std::string, Token_Type> Lexer::keywords = {
    // symbols
    {"neq", Token_Type::NEQ},
    {"<=", Token_Type::LESS_EQUAL},
    {">=", Token_Type::GREATER_EQUAL},
    {"plusminus", Token_Type::PLUS_MINUS},
    {"minusplus", Token_Type::MINUS_PLUS},
    {"sqrt", Token_Type::SQRT},

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

    // greek alphabet
    {"sigma", Token_Type::SIGMA_LOWER},
    {"Sigma", Token_Type::SIGMA_UPPER},
};

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
  case '*':
    push_token(tt::STAR);
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

  case ' ': // ignore whitespaces
  case '\r':
  case '\t':
    break;
  case '\n':
    _line++;
    break;

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
