#ifndef _TOKEN_
#define _TOKEN_

#include "token_type.hpp"
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <ios>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

class Token {
public:
  Token() = default;

  Token(const std::string token, const TokenType type)
      : token_(token), type_(type) {}

  Token(const std::string token) : token_(token) {}

  Token(const TokenType type) : type_(type) {}

  std::string token_;
  TokenType type_;
};

#endif // !_TOKEN_
