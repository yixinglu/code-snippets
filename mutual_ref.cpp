#include <memory>
#include <iostream>
#include "memchk.h"

using namespace std;

struct Bar;
struct Foo{
  shared_ptr<Bar> bar;	
};

struct Bar {
  shared_ptr<Foo> foo;
};

struct Bar2 {
  weak_ptr<Foo> foo;
};

shared_ptr<Bar2> b2ptr(new Bar2());

void check_expired(const weak_ptr<Foo>& ptr) {
  if (ptr.expired()) {
    cout << "expired" << endl;
  }
  else {
    cout << "not expired" << endl;
  }
}

void test() {
  //auto fptr = make_shared<Foo>();
  //auto bptr = make_shared<Bar>();
  shared_ptr<Foo> fptr(new Foo());
  shared_ptr<Bar> bptr(new Bar());
  fptr->bar = bptr;
  bptr->foo = fptr;
  auto f2ptr = make_shared<Foo>();
  b2ptr->foo = f2ptr;
  check_expired(b2ptr->foo);
}

int main() {
  test();
  check_expired(b2ptr->foo);

  MEM_CHK_EXIT_DBG
  return 0;
}
