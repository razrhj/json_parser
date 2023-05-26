#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

int main() {
  std::unique_ptr<int> p(new int(5));
  int x = *p;

  printf("x: %d, *p: %d\n", x, *p);

  return 0;
}
