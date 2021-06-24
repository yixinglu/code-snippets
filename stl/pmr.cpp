#include <iostream>
#include <memory_resource>

using std::cout;
using std::endl;
using std::pmr::vector;

int main() {
  vector<int> vec = {1, 2, 3};
  for (auto i : vec) {
    cout << i << ", ";
  }
  cout << endl;

  return 0;
}
