#ifndef _JSON_DATA_NEW_
#define _JSON_DATA_NEW_

#include "Scanner.hpp"
#include "token.hpp"
#include "token_type.hpp"
#include <cstddef>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <valarray>
#include <vector>

namespace json_data {

struct Value;
struct Array;
struct Object;

struct Value {

  std::vector<std::vector<std::string>> parents_;
  std::string type_;

  union {
    std::string str_;
    std::string num_;
    std::string boolean_;
    std::string null_;

    std::unique_ptr<Object> obj_;
    std::unique_ptr<Array> arr_;
  };

  Value() {}

  Value(std::vector<std::string> &parents, const std::string &type,
        const std::string &basic)
      : type_(type) {

    parents_.emplace_back(parents);

    if (type == "String" || type == "Key") {
      new (&str_) std::string(basic);
    }
    if (type == "Number") {
      new (&num_) std::string(basic);
    }
    if (type == "Boolean") {
      new (&boolean_) std::string(basic);
    }
    if (type == "Null") {
      new (&null_) std::string(basic);
    }
  }

  Value(std::vector<std::string> &parents, const std::string &type,
        const Object &object);

  Value(std::vector<std::string> &parents, const std::string &type,
        const Array &array);

  Value(const Value &value);

  Value &operator=(const Value &value);

  ~Value();
};

struct Object {

  bool empty_;

  std::unordered_map<std::string, Value> kvs_;

  Object() { empty_ = true; }

  Object(const Object &object) {

    empty_ = object.empty_;

    kvs_ = object.kvs_;
  }

  Object &operator=(const Object &object) {

    empty_ = object.empty_;

    kvs_ = object.kvs_;

    return *this;
  }

  ~Object() {}
};

struct Array {

  bool empty_;

  std::vector<Value> vals_;

  Array() { empty_ = true; }

  Array(const Array &array) {

    empty_ = array.empty_;

    vals_ = array.vals_;
  }

  Array &operator=(const Array &array) {
    empty_ = array.empty_;

    vals_ = array.vals_;

    return *this;
  }

  ~Array() {}
};

} // namespace json_data

#endif // !_JSON_DATA_NEW_
