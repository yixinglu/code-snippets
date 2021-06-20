#include <ext/pool_allocator.h>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

template <typename T>
using pool_alloc = __gnu_cxx::__pool_alloc<T>;

int main() {
  vector<int> vec;
  vec.emplace_back(1);
  vec.emplace_back(2);
  vec.emplace_back(3);
  cout << &vec[0] << ", " << &vec[1] << ", " << &vec[2] << endl;

  vector<int, pool_alloc<int>> vec2;
  vec2.emplace_back(1);
  vec2.emplace_back(2);
  vec2.emplace_back(3);
  cout << &vec2[0] << ", " << &vec2[1] << ", " << &vec2[2] << endl;

  int **parr = new int *[3];
  for (int i = 0; i < 3; ++i) {
    parr[i] = new int(i);
  }
  cout << parr[0] << ", " << parr[1] << ", " << parr[2] << endl;
  delete[] parr;

  return 0;
}
