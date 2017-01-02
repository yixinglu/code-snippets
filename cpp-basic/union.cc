#include <iostream>

using namespace std;

enum OpType {
  INVALID,
  KEYBOARD,
  MOUSE
};

struct Head {
  OpType type;
};

struct Keyboard {
  OpType type;
  int key;
};

struct Mouse {
  OpType type;
  int x;
  int y;
};

union Any {
  Head head;
  Keyboard keyboard;
  Mouse mouse;
};

void test(const Any &any) {
  switch (any.head.type) {
  case KEYBOARD:
    cout << "keyboard: " << any.keyboard.key << endl;
    break;
  case MOUSE:
    cout << "mouse:x=" << any.mouse.x << ",y=" << any.mouse.y << endl;
    break;
  default:
    cout << "error" << endl;
  }
}

int main () {
  Keyboard kb = {KEYBOARD, 0};
  test(reinterpret_cast<const Any&>(kb));
  Mouse mouse = {MOUSE, 1, 2};
  test(reinterpret_cast<const Any&>(mouse));

  cout << "Head: " << sizeof(Head) << ", Any: " << sizeof(Any)
       << ", Keyboard: " << sizeof(Keyboard)
       << ", Mouse: " << sizeof(Mouse) << endl;

  return 0;
}
