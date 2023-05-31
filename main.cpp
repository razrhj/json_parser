#include "Scanner.hpp"
#include "basic.hpp"
#include "parser_new.hpp"
#include "query.hpp"
#include <cassert>
#include <cstdio>

int main() {

  Scanner s;

  s.read("demo.json");

  std::vector<Token> tokens = s.getTokens();

  Parser p(tokens);

  p.printTokens();

  assert(p.Start() == ReturnState::Success);

  Query q;

  q.setStringsType(p.getStringsTypes());

  if (q.IsBoolean("true")) {
    for (auto &str : q.getBoolean("true")) {
      printf("%s\n", str.c_str());
    }
  }

  return 0;
}
