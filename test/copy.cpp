#include <iostream>
#include <memory>

using namespace std;

struct Foo {
  Foo(int* i) : iptr(i) { cout << i << endl; }
  unique_ptr<Foo> copy() const { return make_unique<Foo>(*this); }

  // unique_ptr<int> iptr;
  int* iptr{nullptr};
};

int main() {
  int i = 1;
  auto ptr = make_unique<Foo>(&i);
  auto ptr2 = ptr->copy();
  // cout << (*ptr->iptr == *ptr2->iptr) << endl;
  cout << ptr->iptr << endl;
  cout << ptr2->iptr << endl;

  return 0;
}
