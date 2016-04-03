#include <time.h>
#include <iostream>
#include <set>
#include <unordered_set>
#include <cstdlib>

using namespace std;

int main() {
  set<int> s;
  unordered_set<int> us;

  for (int i = 0; i < 100000; ++i) {
    auto k = rand() % 5000;
    s.insert(k);
    us.insert(k);
  }

  auto t = clock();
  for (int i = 0; i < 1000000; ++i) {
    auto k = rand();
    s.find(k);
  }
  cout << "set: " << (double)(clock()-t)/CLOCKS_PER_SEC << endl;
  
  t = clock();
  for (int i = 0; i < 1000000; ++i) {
    auto k = rand();
    us.find(k);
  }
  cout << "unordered_set: " << (double)(clock()-t)/CLOCKS_PER_SEC << endl;

  cout << "size: " << "set " << sizeof s << " " << "unordered_set " << sizeof us << endl;

  return 0;
}
