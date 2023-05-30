#ifndef _QUERY_
#define _QUERY_

#include "json_data_new.hpp"
#include "token_type.hpp"
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

  bool IsKey(const std::string &str) {
    return strings_types_[str]->type_ == TokenType::Key;
  }

  bool IsObject(const std::string &str) {
    return strings_types_[str]->type_ == TokenType::Object;
  }

  bool IsArray(const std::string &str) {
    return strings_types_[str]->type_ == TokenType::Array;
  }

  bool IsNumber(const std::string &str) {
    return strings_types_[str]->type_ == TokenType::Number;
  }

  bool IsBoolean(const std::string &str) {
    return strings_types_[str]->type_ == TokenType::Boolean;
  }

  bool IsNull(const std::string &str) {
    return strings_types_[str]->type_ == TokenType::Null;
  }

  bool IsString(const std::string &str) {
    return strings_types_[str]->type_ == TokenType::String;
  }

  std::vector<std::string> getString(const std::string &str) {
    if (!IsString(str) && !IsKey(str)) {
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
    if (!IsNumber(str)) {
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

    if (!IsBoolean(str)) {
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

    if (!IsNull(str)) {
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
      const std::unordered_map<std::string, std::shared_ptr<json_data::Value>>
          &strings_types) {
    for (auto it = strings_types.begin(); it != strings_types.end(); ++it) {

      if (it->second != nullptr)
        strings_types_[it->first] = std::shared_ptr<json_data::Value>(
            new json_data::Value(*(it->second)));
    }
  }

private:
  std::unordered_map<std::string, std::shared_ptr<json_data::Value>>
      strings_types_;
};

#endif // !_QUERY_
