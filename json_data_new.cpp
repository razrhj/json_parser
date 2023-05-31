#include "json_data_new.hpp"
#include "token_type.hpp"
#include <memory>
#include <string>

json_data::Value::Value(std::vector<std::string> &parents,
                        const TokenType &type, const std::string &basic) {

  parents_.emplace_back(parents);
  type_ = type;

  switch (type_) {

  case TokenType::Key:
  case TokenType::Number:
  case TokenType::String:
  case TokenType::Object:
  case TokenType::Array:
  case TokenType::Boolean:
  case TokenType::Null:
    basic_ = basic;
    break;
  default:
    break;
  }

  /* if (type == "String" || type == "Key") { */
  /*   new (&str_) std::string(basic); */
  /* } */
  /* if (type == "Number") { */
  /*   new (&num_) std::string(basic); */
  /* } */
  /* if (type == "Boolean") { */
  /*   new (&boolean_) std::string(basic); */
  /* } */
  /* if (type == "Null") { */
  /*   new (&null_) std::string(basic); */
  /* } */
}

json_data::Value::Value(const Value &value) {
  parents_ = value.parents_;
  type_ = value.type_;

  basic_ = value.basic_;

  if (value.obj_ != nullptr) {
    obj_ =
        std::unique_ptr<json_data::Object>(new json_data::Object(*value.obj_));
  } else {
    obj_ = nullptr;
  }

  if (value.arr_ != nullptr) {
    arr_ = std::unique_ptr<json_data::Array>(new json_data::Array(*value.arr_));
  } else {
    arr_ = nullptr;
  }
}

json_data::Value::Value(std::vector<std::string> &parents,
                        const TokenType &type, const Object &object)
    : type_(type) {

  parents_.emplace_back(parents);

  switch (type) {

  case TokenType::Object:
    obj_ = std::unique_ptr<json_data::Object>(new json_data::Object(object));
    break;
  default:
    break;
  }
}

json_data::Value::Value(std::vector<std::string> &parents,
                        const TokenType &type, const Array &array)
    : type_(type) {

  parents_.emplace_back(parents);

  switch (type) {

  case TokenType::Array:
    arr_ = std::unique_ptr<json_data::Array>(new json_data::Array(array));
    break;
  default:
    break;
  }
}

json_data::Value &json_data::Value::operator=(const Value &value) {
  parents_ = value.parents_;
  type_ = value.type_;

  basic_ = value.basic_;

  if (value.obj_ != nullptr) {
    obj_ =
        std::unique_ptr<json_data::Object>(new json_data::Object(*value.obj_));
  } else {
    obj_ = nullptr;
  }

  if (value.arr_ != nullptr) {
    arr_ = std::unique_ptr<json_data::Array>(new json_data::Array(*value.arr_));
  } else {
    obj_ = nullptr;
  }

  return *this;
}

json_data::Value::~Value() {

  for (auto &parent : parents_) {
    std::vector<std::string> tmp;
    parent.swap(tmp);
  }

  std::vector<std::vector<std::string>> tmp;

  parents_.swap(tmp);
}
