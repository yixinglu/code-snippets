#include <iostream>
#include <functional>
#include <string>

using namespace std;

using callback = function<void(int)>;

callback closure() {
  int tmp = 10;
  return [=](int i) { cout << (i+tmp) << endl; };
}

function<callback()> closure2() {
  int tmp = 10;
  string str = "hello world";
  return [=]() {
    return [&](int i) { // NOTE
      cout << (i+tmp) << endl;
      cout << str << endl;
    };
  };
}

int main() {
  auto c = closure();
  c(100);

  auto c2 = closure2();
  c2()(200);

  return 0;
}
