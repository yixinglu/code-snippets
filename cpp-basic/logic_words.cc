#include <iostream>

using namespace std;

void test_and(bool a, bool b) {
  if (a and b) {
    cout << "a && b = " << (a && b) << endl;
  }
}

void test_or(bool a, bool b) {
  if (a or b) {
    cout << "a || b = " << (a || b) << endl;
  }
}

void test_not(bool b) {
  if (not b) {
    cout << "!b = " << (!b) << endl;
  }
}

int main() {
  test_and(true, true);
  test_and(false, true);
  test_or(true, false);
  test_or(false, false);
  test_not(true);
  test_not(false);
  return 0;
}
