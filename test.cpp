#include <cstdio>
#include <iostream>
#include <memory>
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

  return 0;
}
