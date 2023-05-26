#include "json_data.hpp"
#include <string>

json_data::Value::Value(const Value &value) {
  parents_ = value.parents_;
  type_ = value.type_;

  if (value.type_ == "String" || value.type_ == "Key") {
    new (&str_) std::string(value.str_);
  }
  if (value.type_ == "Number") {
    new (&num_) std::string(value.num_);
  }
  if (value.type_ == "Boolean") {
    new (&boolean_) std::string(value.boolean_);
  }
  if (value.type_ == "Null") {
    new (&null_) std::string(value.null_);
  }
  if (type_ == "Object") {
    obj_ = new Object(*value.obj_);
  }
  if (type_ == "Array") {
    arr_ = new Array(*value.arr_);
  }
}

json_data::Value::Value(std::vector<std::string> &parents,
                        const std::string &type, const Object &object)
    : type_(type) {

  parents_.emplace_back(parents);

  if (type == "Object") {
    obj_ = new Object(object);
  }
}

json_data::Value::Value(std::vector<std::string> &parents,
                        const std::string &type, const Array &array)
    : type_(type) {

  parents_.emplace_back(parents);

  if (type == "Array") {
    arr_ = new Array(array);
  }
}

json_data::Value &json_data::Value::operator=(const Value &value) {
  parents_ = value.parents_;
  type_ = value.type_;

  if (value.type_ == "String" || value.type_ == "Key") {
    new (&str_) std::string(value.str_);
  }
  if (value.type_ == "Number") {
    new (&num_) std::string(value.num_);
  }
  if (value.type_ == "Boolean") {
    new (&boolean_) std::string(value.boolean_);
  }
  if (value.type_ == "Null") {
    new (&null_) std::string(value.null_);
  }
  if (value.type_ == "Object") {
    obj_ = new json_data::Object(*value.obj_);
  }
  if (value.type_ == "Array") {
    arr_ = new json_data::Array(*value.arr_);
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

  if (type_ == "Object" && obj_ != nullptr) {
    delete obj_;
    obj_ = nullptr;
  }

  if (type_ == "Array" && arr_ != nullptr) {
    delete arr_;
    arr_ = nullptr;
  }
}
