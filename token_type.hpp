#ifndef _TOKEN_TYPE_
#define _TOKEN_TYPE_

#include <string>

enum class TokenType {
  None,
  Key,
  Value,
  Number,
  String,
  Object,
  Array,
  Boolean,
  Null,
  LeftBrace,
  RightBrace,
  LeftBracket,
  RightBracket,
  Quote,
  Comma,
  Colon
};

inline std::string TokenTypeEnumName(TokenType type) {
  switch (type) {
  case TokenType::None:
    return "None";
  case TokenType::Key:
    return "Key";
  case TokenType::Value:
    return "Value";
  case TokenType::Number:
    return "Number";
  case TokenType::String:
    return "String";
  case TokenType::Object:
    return "Object";
  case TokenType::Array:
    return "Array";
  case TokenType::Boolean:
    return "Boolean";
  case TokenType::Null:
    return "Null";
  case TokenType::LeftBrace:
    return "LeftBrace";
  case TokenType::RightBrace:
    return "RightBrace";
  case TokenType::LeftBracket:
    return "LeftBracket";
  case TokenType::RightBracket:
    return "RightBracket";
  case TokenType::Quote:
    return "Quote";
  case TokenType::Comma:
    return "Comma";
  case TokenType::Colon:
    return "Colon";
  default:
    return "1";
  }
}

#endif // !_TOKEN_TYPE_
