#include <cstdio>
#include <pthread.h>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

#include <iostream>

using namespace std;

enum class TokenType {
  Number,
  String,
  Object,
  Array,
  Null,
  Boolean,
  LeftBrace,
  RightBrace,
  LeftBracket,
  RightBraceket,
  Comma,
  Colon,
  Quote,
};

class Token {
public:
  Token(const string &value, TokenType type) : value_(value), type_(type) {}
  Token(TokenType type) : type_(type) {}

  string value_;
  TokenType type_;
};

class Scanner {
public:
  string readContent() {}

  // bool isObject() {}
  //
  // bool isString() {}
  //
  // bool isNumber() {}
  //
  // bool isBoolean() {}
  //
  // bool isArrary() {}
  //
  // bool isNull() {}

  void parse() {
    auto c = content_[idx_++];
    switch (c) {
    case '{':
      tokens_.emplace_back(TokenType::LeftBrace);
      break;
    case '}':
      tokens_.emplace_back(TokenType::RightBrace);
      break;
    case '[':
      tokens_.emplace_back(TokenType::LeftBracket);
      break;
    case ']':
      tokens_.emplace_back(TokenType::RightBraceket);
      break;
    case '"':
      tokens_.emplace_back(TokenType::Quote);
      // if (!isString()) {
      // }
      break;
    case ':':
      break;
    case '.':
      break;
    case ',':
      break;
    }
  }

private:
  vector<Token> tokens_;
  int idx_;
  string content_;
};

class Parser {
public:
  Parser(vector<Token> tokens) {}

  bool parse() {
    auto token = tokens_[idx_];
    switch (token.type_) {
    case TokenType::Number:

    case TokenType::String:
    case TokenType::Object:
    case TokenType::Array:
    case TokenType::Null:
    case TokenType::Boolean:
    case TokenType::LeftBrace:
    case TokenType::RightBrace:
    case TokenType::LeftBracket:
    case TokenType::RightBraceket:
    case TokenType::Comma:
    case TokenType::Colon:
    case TokenType::Quote:
      break;
    }
  }

  bool Key() { return Advance().type_ == TokenType::String; }

  bool Primary() {
    auto token = Advance().type_;
    switch (token) {
    case TokenType::Number:
    case TokenType::String:
    case TokenType::Null:
    case TokenType::Boolean:
      return true;
    default:
      return false;
    }
  }

  bool KV() { return Key() && Colon() && Value(); }
  bool Array() {}
  bool Value() { return Object() || Array() || Primary(); }
  bool Comma() { return Advance().type_ == TokenType::Comma; }
  bool Colon() { return Advance().type_ == TokenType::Colon; }

  Token Advance() { return tokens_[idx_++]; }

  Token Peek() { return tokens_[idx_]; }

  bool Object() {
    if (Advance().type_ != TokenType::LeftBrace) {
    }

    if (Peek().type_ == TokenType::RightBrace) {

    } else {
      while (1) {
        Key();
        Colon();
        Value();
        if (!Comma()) {
          break;
        }
        // comma
      }
    }

    if (Advance().type_ != TokenType::RightBrace) {
    }
  }

private:
  int idx_;
  vector<Token> tokens_;
};

int main() {}
