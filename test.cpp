#include <cstdio>
#include <iostream>
#include <memory>
#include <regex>
#include <string>

class A {
public:
  A();
  A(A &&) = default;
  A(const A &) = default;
  A &operator=(A &&) = default;
  A &operator=(const A &) = default;
  ~A();

  void func() {
    a = 1;
    printf("a = %d\n", a);
  }

private:
  int a;
};

A::A() {}

A::~A() {}

int main() {
  std::unique_ptr<A> aptr(new A());

  A a = *aptr;

  a.func();

  std::regex array_match(R"(Aray[0-9]*)");

  if (std::regex_match("Array1111", array_match)) {
    printf("true\n");
  } else {
    printf("false\n");
  }

  std::regex key_match(R"(<.*>)");

  if (std::regex_match("<adfHI>", key_match)) {
    printf("true\n");
  } else {
    printf("false\n");
  }

  return 0;
}
