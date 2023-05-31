#ifndef _QUERY_
#define _QUERY_

#include "json_data_new.hpp"
#include "token_type.hpp"
#include <cstdio>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Query {
public:
  Query() = default;
  Query(Query &&) = default;
  Query(const Query &) = default;
  Query &operator=(Query &&) = default;
  Query &operator=(const Query &) = default;
  ~Query() {}

  bool isKey(const std::string &str) {
    return strings_types_[str]->type_ == TokenType::Key;
  }

  bool isObject(const std::string &str) {
    return strings_types_[str]->type_ == TokenType::Object;
  }

  bool isArray(const std::string &str) {
    return strings_types_[str]->type_ == TokenType::Array;
  }

  bool isNumber(const std::string &str) {
    return strings_types_[str]->type_ == TokenType::Number;
  }

  bool isBoolean(const std::string &str) {
    return strings_types_[str]->type_ == TokenType::Boolean;
  }

  bool isNull(const std::string &str) {
    return strings_types_[str]->type_ == TokenType::Null;
  }

  bool isString(const std::string &str) {
    return strings_types_[str]->type_ == TokenType::String;
  }

  void printValue(json_data::Value &value) {
    /* printf("type: %s\n", TokenTypeEnumName(value.type_).c_str()); */
    switch (value.type_) {

    case TokenType::Number:
    case TokenType::String:
    case TokenType::Boolean:
    case TokenType::Null:
      printf("%s\n", value.basic_.c_str());
      break;
    case TokenType::Object:
      if (value.obj_) {
        printObject(*value.obj_);
      } else {
        printf("nullptr\n");
      }
      break;
    case TokenType::Array:
      if (value.arr_) {
        printArray(*value.arr_);
      }
      break;
    default:
      break;
    }
  }

  void printObject(json_data::Object &obj) {
    if (!obj.empty_) {
      printf("Object size: %lu\n", obj.kvs_.size());
      for (auto &[key, value] : obj.kvs_) {
        printf("\"%s\" : ", key.c_str());
        printValue(value);
        printf("\n");
      }
    }
  }

  void printArray(json_data::Array &arr) {
    if (!arr.empty_) {
      printf("Array size: %lu\n", arr.vals_.size());
      for (auto &value : arr.vals_) {
        printValue(value);
        printf("\n");
      }
    }
  }

  json_data::Object getObject(const std::string &str) {
    if (!isObject(str)) {
      return json_data::Object();
    }

    printObject(*strings_types_[str]->obj_);

    return *strings_types_[str]->obj_;
  }

  json_data::Array getArray(const std::string &str) {
    if (!isArray(str)) {
      return json_data::Array();
    }

    printArray(*strings_types_[str]->arr_);

    return *strings_types_[str]->arr_;
  }

  std::vector<std::string> getString(const std::string &str) {
    if (!isString(str) && !isKey(str)) {
      return {};
    }

    std::vector<std::string> ret;

    for (auto &parents : strings_types_[str]->parents_) {
      std::string temp;
      for (auto &parent : parents) {
        temp += parent + "->";
      }
      temp += strings_types_[str]->basic_;
      ret.emplace_back(temp);
    }
    return ret;
  }

  std::vector<std::string> getNumber(const std::string &str) {
    if (!isNumber(str)) {
      return {};
    }

    std::vector<std::string> ret;

    for (auto &parents : strings_types_[str]->parents_) {
      std::string temp;
      for (auto &parent : parents) {
        temp += parent + "->";
      }
      temp += strings_types_[str]->basic_;
      ret.emplace_back(temp);
    }
    return ret;
  }

  std::vector<std::string> getBoolean(const std::string &str) {

    if (!isBoolean(str)) {
      return {};
    }

    std::vector<std::string> ret;

    for (auto &parents : strings_types_[str]->parents_) {
      std::string temp;
      for (auto &parent : parents) {
        temp += parent + "->";
      }
      temp += strings_types_[str]->basic_;
      ret.emplace_back(temp);
    }
    return ret;
  }

  std::vector<std::string> getNull(const std::string &str) {

    if (!isNull(str)) {
      return {};
    }

    std::vector<std::string> ret;

    for (auto &parents : strings_types_[str]->parents_) {
      std::string temp;
      for (auto &parent : parents) {
        temp += parent + "->";
      }
      temp += strings_types_[str]->basic_;
      ret.emplace_back(temp);
    }
    return ret;
  }

  void setStringsType(
      const std::unordered_map<std::string, std::unique_ptr<json_data::Value>>
          &strings_types) {

    for (auto &[first, second] : strings_types) {
      strings_types_[first] =
          std::unique_ptr<json_data::Value>(new json_data::Value(*second));
    }
  }

private:
  std::unordered_map<std::string, std::unique_ptr<json_data::Value>>
      strings_types_;
};

#endif // !_QUERY_
