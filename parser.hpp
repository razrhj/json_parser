#ifndef _PARSER_
#define _PARSER_

#include "basic.hpp"
#include "json_data.hpp"
#include "token.hpp"
#include "token_type.hpp"
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <ios>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

class Parser {
public:
  Parser() = default;

  ~Parser() {
    std::vector<std::string> tmp1;
    parents.swap(tmp1);

    for (auto it = strings_types_.begin(); it != strings_types_.end(); ++it) {
      if (it->second != nullptr) {
        if (it->second->type_ == "Object" && it->second->obj_ != nullptr) {
          delete it->second->obj_;
          it->second->obj_ = nullptr;
        }
        if (it->second->type_ == "Array" && it->second->arr_ != nullptr) {
          delete it->second->arr_;
          it->second->arr_ = nullptr;
        }

        delete it->second;
        it->second = nullptr;
      }
    }
    std::unordered_map<std::string, json_data::Value *> tmp2;
    strings_types_.swap(tmp2);
  }

  Parser(std::vector<Token> tokens) : tokens_(tokens) {}

  void Advance() { idx_++; }

  Token &Peek() {
    if (idx_ < tokens_.size()) {
      printf("parents: \n");
      for (auto &str : parents) {
        printf("%s->", str.c_str());
      }
      printf("\nidx<%d>   token<%s>   type<%s>\n", idx_,
             tokens_[idx_].token_.c_str(),
             TokenTypeEnumName(tokens_[idx_].type_).c_str());
      return tokens_[idx_];
    }
    return error_;
  }

  ReturnState LeftBrace();

  ReturnState RightBrace();

  ReturnState LeftBracket();

  ReturnState RightBracket();

  ReturnState Comma();

  ReturnState Colon();

  ReturnState Quote();

  ReturnState Start();

  ReturnState KeyValue();

  ReturnState Key();

  ReturnState Value();

  ReturnState Object();

  ReturnState Array();

  ReturnState Primary();

  ReturnState Number();

  ReturnState Boolean();

  ReturnState Null();

  ReturnState String(const std::string caller);

  void printTokens() {
    for (auto &token : tokens_) {
      printf("%s", token.token_.c_str());

      // printf("token: %s, type: %s\n", token.token_.c_str(),
      //        EnumName(token.type_).c_str());
    }
    printf("\n");
  }

  std::unordered_map<std::string, json_data::Value *> getStringsTypes() {
    return strings_types_;
  }

private:
  std::vector<Token> tokens_;
  Token error_ = Token("None", TokenType::None);
  int idx_ = 0;
  std::unordered_map<std::string, json_data::Value *> strings_types_;
  std::vector<std::string> parents;
  int objects_id = 0;
  int arrays_id = 0;
};

#endif // !_PARSER_
