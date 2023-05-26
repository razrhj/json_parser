#ifndef _SCANNER_
#define _SCANNER_

#include "basic.hpp"
#include "token.hpp"
#include <cstdio>

class Scanner {
public:
  bool isBlank(char c) {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v' ||
           c == '\b' || c == '\f';
  }

  bool isSeparator(char c) {
    return c == '{' || c == '}' || c == '[' || c == ']' || c == '"' ||
           c == ':' || c == ',';
  }

  void readInQuote();

  void readString();

  ReturnState read(const std::string file_path);

  void printTokens() {
    for (auto &token : tokens) {
      printf("%s", token.token_.c_str());

      // printf("token: %s, type: %s\n", token.token_.c_str(),
      //        TokenTypeEnumName(token.type_).c_str());
    }
    printf("\n");
  }

  std::vector<Token> getTokens() { return tokens; }

private:
  std::vector<Token> tokens;
  std::string buffer;
  int i;
};

#endif // !_SCANNER_
