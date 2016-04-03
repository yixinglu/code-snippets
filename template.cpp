#include <iostream>

template<typename T>
void print(const T&) {
// == void print(T const &) {
  std::cout << "template" << std::endl;
}

template<>
void print<char*>(char *const &) {
// != void print<char*>(const char*&) {
  std::cout << "specialization" << std::endl;
}

void print(const char*) {
  std::cout << "not template" << std::endl;
}

int main(int argc, char* argv[]) {
  char* p = "hello";
  const char* pc = p;
  const char pa[] = "hello";
  print(p);
  print(pc);
  print(pa);
  return 0;
}
