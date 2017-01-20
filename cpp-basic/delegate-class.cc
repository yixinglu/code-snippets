#include <iostream>

using namespace std;

struct Foo {
  Foo(int i) : i(i) { cout << "i: " << i << endl; }
  Foo() : Foo(0) { cout << "delegate class" << endl; }
  int i;
};

int main() {
  Foo f(1), bar;
  return 0;
}
