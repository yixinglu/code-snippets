#include <iostream>
#include <memory>

using namespace std;

class Foo : public enable_shared_from_this<Foo> {
 public:
  shared_ptr<Foo> get_shared_ptr() {
    cout << "Foo::get_shared_ptr()" << endl;
    return shared_from_this();
  }
};

class Bar {
 public:
  shared_ptr<Bar> get_shared_ptr() {
    cout << "Bar::get_shared_ptr()" << endl;
    return shared_ptr<Bar>(this); // dangerous
  }
};

int main() {
  shared_ptr<Foo> foo(new Foo);
  // auto f1 = foo;
  auto f2 = foo->get_shared_ptr();

  shared_ptr<Bar> bar(new Bar);
  auto b2 = bar->get_shared_ptr();
  // auto b1 = bar;
  return 0;
}
