// private and protected inheritance example

#include <iostream>

struct Interface {
  virtual void print() const = 0;
};

class Base : protected Interface {
public:
  virtual void print() const {
    std::cout << "Base" << std::endl;
  }
};

class Drive : private Base {
  friend void test();
public:
  virtual void print() const {
    std::cout << "Drive" << std::endl;
  }
};

void test() {
  Interface* p = new Drive();
  p->print();
  delete p;
}

void test1() {
  // error: can not compile

  // Base* p = new Drive();
  // p->print();
  // delete p;
}

int main(int argc, char** argv) {
  test();
  return 0;
}
