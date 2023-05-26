#include "Scanner.hpp"

void Scanner::readInQuote() {
  std::string temp;

  while (i < buffer.size() && buffer[i] != '"') {
    temp.push_back(buffer[i]);
    i++;
  }

  tokens.emplace_back(Token(temp, TokenType::String));

  if (i < buffer.size() && buffer[i] == '\"') {
    tokens.emplace_back(Token("\"", TokenType::Quote));
  }
}

void Scanner::readString() {
  if (i < buffer.size()) {
    if (isSeparator(buffer[i])) {
      i--;
    } else {
      std::string temp;

      while (i < buffer.size() && !isSeparator(buffer[i])) {
        while (i < buffer.size() && isBlank(buffer[i])) {
          i++;
        }

        if (i >= buffer.size()) {
          return;
        }

        if (isSeparator(buffer[i])) {
          i--;
          return;
        }

        while (i < buffer.size() &&
               (!isBlank(buffer[i]) && !isSeparator(buffer[i]))) {
          temp.push_back(buffer[i]);
          i++;
        }

        tokens.emplace_back(Token(temp, TokenType::String));

        if (i >= buffer.size()) {
          return;
        }

        if (isSeparator(buffer[i])) {
          i--;
          return;
        }
      }
    }
  }
}

ReturnState Scanner::read(const std::string file_path) {
  std::ifstream fp;
  fp.open(file_path, std::ios_base::in);
  if (!fp.is_open()) {
    return ReturnState::OpenFileFailed;
  }

  std::string line;
  while (getline(fp, line, '\n')) {
    buffer += line + '\n';
  }

  // std::cout << buffer << std::endl;

  for (i = 0; i < buffer.size(); ++i) {
    switch (buffer[i]) {
    case ' ':
    case '\n':
    case '\r':
    case '\t':
    case '\v':
    case '\b':
    case '\f':
      break;
    case '{':
      tokens.emplace_back(Token("{", TokenType::LeftBrace));
      break;
    case '}':
      tokens.emplace_back(Token("}", TokenType::RightBrace));
      break;
    case '[':
      tokens.emplace_back(Token("[", TokenType::LeftBracket));
      break;
    case ']':
      tokens.emplace_back(Token("]", TokenType::RightBracket));
      break;
    case '"': {
      tokens.emplace_back(Token("\"", TokenType::Quote));
      i++;
      readInQuote();
      break;
    }
    case ',':
      tokens.emplace_back(Token(",", TokenType::Comma));
      break;
    case ':': {
      tokens.emplace_back(Token(":", TokenType::Colon));
      break;
    }
    default:
      readString();
      break;
    }
  }
  return ReturnState::Success;
}
