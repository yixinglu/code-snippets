
#include <cstdint>
#include <iostream>

struct foo {
  uint32_t bar;
};

int main() {
  foo foo{1024};
  std::cout << foo.bar << std::endl;
  return 0;
}
