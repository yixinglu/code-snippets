#include <iostream>

using namespace std;

struct Foo {
  Foo &operator+(int i) {
    cout << "operator +" << endl;
    return *this;
  }
};

Foo &operator+(int i, Foo &foo) { return foo + i; }

int main() {
  Foo foo;
  int i = 0;
  i + foo + i;

  return 0;
}
