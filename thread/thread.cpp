#include <iostream>
#include <thread>

using namespace std;

void task(int x) {
  for (int i = x; i < x+100; ++i) {
    cout << i << endl;
  }
}

int main() {
  thread t1(task, 1);
  thread t2(task, 100);
  t1.join();
  t2.join();
  return 0;
}
