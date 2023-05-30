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

  switch (value.type_) {

  case TokenType::Key:
  case TokenType::Number:
  case TokenType::String:
  case TokenType::Boolean:
  case TokenType::Null:
    basic_ = value.basic_;
    break;
  case TokenType::Object:
    obj_ =
        std::unique_ptr<json_data::Object>(new json_data::Object(*value.obj_));
    break;
  case TokenType::Array:
    arr_ = std::unique_ptr<json_data::Array>(new json_data::Array(*value.arr_));
    break;

  default:
    break;
  }

  /* if (value.type_ == "String" || value.type_ == "Key") { */
  /*   new (&str_) std::string(value.str_); */
  /* } */
  /* if (value.type_ == "Number") { */
  /*   new (&num_) std::string(value.num_); */
  /* } */
  /* if (value.type_ == "Boolean") { */
  /*   new (&boolean_) std::string(value.boolean_); */
  /* } */
  /* if (value.type_ == "Null") { */
  /*   new (&null_) std::string(value.null_); */
  /* } */
  /* if (type_ == "Object") { */
  /*   obj_ = */
  /*       std::unique_ptr<json_data::Object>(new
   * json_data::Object(*value.obj_)); */
  /* } */
  /* if (type_ == "Array") { */
  /*   arr_ = std::unique_ptr<json_data::Array>(new
   * json_data::Array(*value.arr_)); */
  /* } */
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

  /* if (type == "Object") { */
  /*   obj_ = std::unique_ptr<json_data::Object>(new json_data::Object(object));
   */
  /* } */
}

json_data::Value::Value(std::vector<std::string> &parents,
                        const TokenType &type, const Array &array)
    : type_(type) {

  parents_.emplace_back(parents);

  switch (type) {

  case TokenType::Object:
    arr_ = std::unique_ptr<json_data::Array>(new json_data::Array(array));
    break;
  default:
    break;
  }

  /* if (type == "Array") { */
  /*   arr_ = std::unique_ptr<json_data::Array>(new json_data::Array(array)); */
  /* } */
}

json_data::Value &json_data::Value::operator=(const Value &value) {
  parents_ = value.parents_;
  type_ = value.type_;

  switch (value.type_) {

  case TokenType::Key:
  case TokenType::Number:
  case TokenType::String:
  case TokenType::Boolean:
  case TokenType::Null:
    basic_ = value.basic_;
    break;
  case TokenType::Object:
    obj_ =
        std::unique_ptr<json_data::Object>(new json_data::Object(*value.obj_));
    break;
  case TokenType::Array:
    arr_ = std::unique_ptr<json_data::Array>(new json_data::Array(*value.arr_));
    break;

  default:
    break;
  }

  /* if (value.type_ == "String" || value.type_ == "Key") { */
  /*   new (&str_) std::string(value.str_); */
  /* } */
  /* if (value.type_ == "Number") { */
  /*   new (&num_) std::string(value.num_); */
  /* } */
  /* if (value.type_ == "Boolean") { */
  /*   new (&boolean_) std::string(value.boolean_); */
  /* } */
  /* if (value.type_ == "Null") { */
  /*   new (&null_) std::string(value.null_); */
  /* } */
  /* if (value.type_ == "Object") { */
  /*   obj_ = */
  /*       std::unique_ptr<json_data::Object>(new
   * json_data::Object(*value.obj_)); */
  /* } */
  /* if (value.type_ == "Array") { */
  /*   arr_ = std::unique_ptr<json_data::Array>(new
   * json_data::Array(*value.arr_)); */
  /* } */

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
