#include <iostream>
#include <functional>

using namespace std;

void print(const char* str) {
  cout << str << endl;
}

int main() {
  auto printHello = []() { print("hello");};
  function<void()> printHello1 = bind(&print, "hello");
  printHello();
  printHello1();
  return 0;
}
