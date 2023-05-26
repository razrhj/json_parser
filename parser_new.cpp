#include "parser_new.hpp"
#include "basic.hpp"
#include "json_data_new.hpp"
#include "token_type.hpp"
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

ReturnState Parser::LeftBrace() {
  if (Peek().type_ == TokenType::LeftBrace) {

    Advance();

    printf("LeftBrace Success\n");
    return ReturnState::Success;
  }
  printf("Not LeftBrace\n");
  return ReturnState::NotLeftBrace;
}

ReturnState Parser::RightBrace() {
  if (Peek().type_ == TokenType::RightBrace) {

    Advance();

    printf("RightBrace Success\n");
    return ReturnState::Success;
  }
  printf("Not RightBrace\n");
  return ReturnState::NotRightBrace;
}

ReturnState Parser::LeftBracket() {
  if (Peek().type_ == TokenType::LeftBracket) {

    Advance();

    printf("LeftBracket Success\n");
    return ReturnState::Success;
  }
  printf("Not LeftBracket\n");
  return ReturnState::NotLeftBracket;
}

ReturnState Parser::RightBracket() {
  if (Peek().type_ == TokenType::RightBracket) {

    Advance();

    printf("RightBracket Success\n");
    return ReturnState::Success;
  }
  printf("Not RightBracket\n");
  return ReturnState::NotRightBracket;
}

ReturnState Parser::Comma() {
  if (Peek().type_ == TokenType::Comma) {

    Advance();

    printf("Comma Success\n");
    return ReturnState::Success;
  }
  printf("Not Comma\n");
  return ReturnState::NotComma;
}

ReturnState Parser::Colon() {
  if (Peek().type_ == TokenType::Colon) {

    Advance();

    printf("Colon Success\n");
    return ReturnState::Success;
  }
  printf("Not Colon\n");
  return ReturnState::NotColon;
}

ReturnState Parser::Quote() {
  if (Peek().type_ == TokenType::Quote) {

    Advance();

    printf("Quote Success\n");
    return ReturnState::Success;
  }
  printf("Not Quote\n");
  return ReturnState::NotQuote;
}

ReturnState Parser::Start() {
  parents.emplace_back("Start");
  if (Object() == ReturnState::Success || Array() == ReturnState::Success) {

    printf("Start Success\n");
    return ReturnState::Success;
  }
  printf("Start Error\n");
  return ReturnState::StartError;
}

ReturnState Parser::KeyValue() {
  if (Key() == ReturnState::Success) {
    if (Colon() == ReturnState::Success) {
      if (Value() == ReturnState::Success) {

        printf("KV Success\n");
        return ReturnState::Success;
      }
    }
  }
  printf("KV Error\n");
  return ReturnState::KVError;
}

ReturnState Parser::Key() {
  if (Quote() == ReturnState::Success) {

    if (String("Key") == ReturnState::Success) {

      if (Quote() == ReturnState::Success) {

        printf("Key Success\n");
        return ReturnState::Success;
      }
    }
  }
  printf("Key Error\n");
  return ReturnState::KeyError;
}

ReturnState Parser::Value() {
  if (Primary() == ReturnState::Success || Array() == ReturnState::Success ||
      Object() == ReturnState::Success) {

    printf("Value Success\n");
    return ReturnState::Success;
  }

  printf("Value Error\n");
  return ReturnState::ValueError;
}

ReturnState Parser::Object() {

  const std::string obj = "Object" + std::to_string(objects_id);
  parents.emplace_back(obj);
  objects_id++;
  strings_types_[obj] = std::unique_ptr<json_data::Value>(
      new json_data::Value(parents, "Object", json_data::Object()));
  // strings_types_[obj] = new json_data::Value();
  // strings_types_[obj]->type_ = "Object";
  // strings_types_[obj]->obj_ = new json_data::Object();

  if (LeftBrace() == ReturnState::Success) {
    if (RightBrace() == ReturnState::Success) {

      parents.pop_back();

      if (parents.back() == "Key") {

        strings_types_[obj]->parents_.back().pop_back();

        const std::string &key = parents.back();
        parents.pop_back();
        parents.pop_back();

        const std::string pre_obj = parents.back();

        strings_types_[pre_obj]->obj_->kvs_[key] = *strings_types_[obj];
      }
      if (parents.back() == "Array") {
        const std::string &pre_arr = parents.back();

        strings_types_[pre_arr]->arr_->vals_.emplace_back(*strings_types_[obj]);
      }

      return ReturnState::Success;
    } else {

      while (Peek().type_ != error_.type_) {
        if (KeyValue() == ReturnState::Success) {
          if (Comma() != ReturnState::Success) {
            break;
          }
        } else {

          objects_id--;
          parents.pop_back();

          printf("Object Error\n");
          return ReturnState::ObjectError;
        }
      }
      if (Peek().type_ != error_.type_ &&
          RightBrace() == ReturnState::Success) {

        parents.pop_back();

        if (parents.back() == "Key") {

          strings_types_[obj]->parents_.back().pop_back();

          const std::string &key = parents.back();
          parents.pop_back();
          parents.pop_back();

          const std::string pre_obj = parents.back();

          strings_types_[pre_obj]->obj_->kvs_[key] = *strings_types_[obj];
        }
        if (parents.back() == "Array") {
          const std::string &pre_arr = parents.back();

          strings_types_[pre_arr]->arr_->vals_.emplace_back(
              *strings_types_[obj]);
        }

        printf("Object Success\n");
        return ReturnState::Success;
      }
    }
  }

  objects_id--;
  parents.pop_back();

  printf("Object Error\n");
  return ReturnState::ObjectError;
}

ReturnState Parser::Array() {

  const std::string arr = "Array" + std::to_string(arrays_id);
  parents.emplace_back(arr);
  arrays_id++;
  strings_types_[arr] = std::unique_ptr<json_data::Value>(
      new json_data::Value(parents, "Array", json_data::Array()));
  // strings_types_[arr] = new json_data::Value();
  // strings_types_[arr]->type_ = "Array";
  // strings_types_[arr]->arr_ = new json_data::Array();

  if (LeftBracket() == ReturnState::Success) {
    if (RightBracket() == ReturnState::Success) {

      parents.pop_back();

      if (parents.back() == "Key") {

        strings_types_[arr]->parents_.back().pop_back();

        const std::string &key = parents.back();
        parents.pop_back();
        parents.pop_back();

        const std::string &pre_obj = parents.back();

        strings_types_[pre_obj]->obj_->kvs_[key] = *strings_types_[arr];
      }
      if (parents.back() == "Array") {

        const std::string &pre_arr = parents.back();

        strings_types_[pre_arr]->arr_->vals_.emplace_back(*strings_types_[arr]);
      }

      printf("Array Success\n");
      return ReturnState::Success;
    } else {
      while (Peek().type_ != error_.type_) {
        if (Value() == ReturnState::Success) {
          if (Comma() != ReturnState::Success) {
            break;
          }
        } else {

          arrays_id--;
          parents.pop_back();

          printf("Array Error\n");
          return ReturnState::ArrayError;
        }
      }
      if (Peek().type_ != error_.type_ &&
          RightBracket() == ReturnState::Success) {

        parents.pop_back();

        if (parents.back() == "Key") {

          strings_types_[arr]->parents_.back().pop_back();

          const std::string &key = parents.back();
          parents.pop_back();
          parents.pop_back();

          const std::string &pre_obj = parents.back();

          strings_types_[pre_obj]->obj_->kvs_[key] = *strings_types_[arr];
        }
        if (parents.back() == "Array") {

          const std::string &pre_arr = parents.back();

          strings_types_[pre_arr]->arr_->vals_.emplace_back(
              *strings_types_[arr]);
        }

        printf("Array Success\n");
        return ReturnState::Success;
      }
    }
  }

  arrays_id--;
  parents.pop_back();

  printf("Array Error\n");
  return ReturnState::ArrayError;
}

ReturnState Parser::Primary() {
  if (Number() == ReturnState::Success || Boolean() == ReturnState::Success ||
      Null() == ReturnState::Success ||
      (Quote() == ReturnState::Success &&
       String("Primary") == ReturnState::Success &&
       Quote() == ReturnState::Success)) {

    printf("Primary Success\n");
    return ReturnState::Success;
  }

  printf("Primary Error\n");
  return ReturnState::PrimaryError;
}

ReturnState Parser::Number() {
  const std::regex number_regex(R"(-?(0|[1-9][0-9]*)(\.[0-9]+)?)");
  if (std::regex_match(Peek().token_, number_regex)) {
    Peek().type_ = TokenType::Number;
  }

  if (Peek().type_ == TokenType::Number) {

    if (!strings_types_.count(Peek().token_)) {

      strings_types_[Peek().token_] = std::unique_ptr<json_data::Value>(
          new json_data::Value(parents, "Number", Peek().token_));

    } else {

      strings_types_[Peek().token_]->parents_.emplace_back(parents);
    }

    if (parents.back() == "Key") {

      strings_types_[Peek().token_]->parents_.back().pop_back();

      std::string &key = parents.back();
      parents.pop_back();
      parents.pop_back();

      std::string &pre_obj = parents.back();

      strings_types_[pre_obj]->obj_->kvs_[key] = *strings_types_[Peek().token_];
    }

    if (parents.back() == "Array") {

      const std::string pre_arr = parents.back();

      strings_types_[Peek().token_]->arr_->vals_.emplace_back(
          *strings_types_[Peek().token_]);
    }

    Advance();

    printf("Number Success\n");
    return ReturnState::Success;
  }
  printf("Wrong Number Format\n");
  return ReturnState::WrongNumberFormat;
}

ReturnState Parser::Boolean() {
  if (Peek().token_ == "true" || Peek().token_ == "false") {
    Peek().type_ = TokenType::Boolean;
  }

  if (Peek().type_ == TokenType::Boolean) {

    if (!strings_types_.count(Peek().token_)) {

      strings_types_[Peek().token_] = std::unique_ptr<json_data::Value>(
          new json_data::Value(parents, "Boolean", Peek().token_));

    } else {

      strings_types_[Peek().token_]->parents_.emplace_back(parents);
    }

    if (parents.back() == "Key") {

      strings_types_[Peek().token_]->parents_.back().pop_back();

      std::string &key = parents.back();
      parents.pop_back();
      parents.pop_back();

      std::string &pre_obj = parents.back();

      strings_types_[pre_obj]->obj_->kvs_[key] = *strings_types_[Peek().token_];
    }

    if (parents.back() == "Array") {

      const std::string pre_arr = parents.back();

      strings_types_[Peek().token_]->arr_->vals_.emplace_back(
          *strings_types_[Peek().token_]);
    }

    Advance();

    printf("Boolean Success\n");
    return ReturnState::Success;
  }
  printf("Wrong Boolean Format\n");
  return ReturnState::WrongBooleanFormat;
}

ReturnState Parser::Null() {
  if (Peek().token_ == "null") {
    Peek().type_ = TokenType::Null;
  }

  if (Peek().type_ == TokenType::Null) {

    if (!strings_types_.count(Peek().token_)) {

      strings_types_[Peek().token_] = std::unique_ptr<json_data::Value>(
          new json_data::Value(parents, "Null", Peek().token_));

    } else {

      strings_types_[Peek().token_]->parents_.emplace_back(parents);
    }

    if (parents.back() == "Key") {

      strings_types_[Peek().token_]->parents_.back().pop_back();

      std::string &pre_obj = parents.back();

      std::string &key = parents.back();
      parents.pop_back();
      parents.pop_back();

      strings_types_[pre_obj]->obj_->kvs_[key] = *strings_types_[Peek().token_];
    }

    if (parents.back() == "Array") {

      const std::string pre_arr = parents.back();

      strings_types_[Peek().token_]->arr_->vals_.emplace_back(
          *strings_types_[Peek().token_]);
    }

    Advance();

    printf("Null Success\n");
    return ReturnState::Success;
  }
  printf("Wrong Null Format\n");
  return ReturnState::WrongNullFormat;
}

ReturnState Parser::String(const std::string caller) {
  if (Peek().type_ == TokenType::String) {

    if (caller == "Key") {

      if (!strings_types_.count(Peek().token_)) {

        strings_types_[Peek().token_] = std::unique_ptr<json_data::Value>(
            new json_data::Value(parents, "Key", Peek().token_));

      } else {

        strings_types_[Peek().token_]->parents_.emplace_back(parents);
      }

      parents.emplace_back("<" + Peek().token_ + ">");
      parents.emplace_back("Key");
    }

    if (caller == "Primary") {

      if (!strings_types_.count(Peek().token_)) {

        strings_types_[Peek().token_] = std::unique_ptr<json_data::Value>(
            new json_data::Value(parents, "String", Peek().token_));

      } else {

        strings_types_[Peek().token_]->parents_.emplace_back(parents);
      }

      if (parents.back() == "Key") {

        strings_types_[Peek().token_]->parents_.back().pop_back();

        const std::string &key = parents.back();
        parents.pop_back();
        parents.pop_back();

        const std::string &pre_obj = parents.back();

        strings_types_[pre_obj]->obj_->kvs_[key] =
            *strings_types_[Peek().token_];
      }
      if (parents.back() == "Array") {
        const std::string &pre_arr = parents.back();

        strings_types_[pre_arr]->arr_->vals_.emplace_back(
            *strings_types_[Peek().token_]);
      }
    }

    Advance();
    printf("String Success\n");
    return ReturnState::Success;
  }
  printf("Wrong String Format\n");
  return ReturnState::WrongStringFormat;
}
