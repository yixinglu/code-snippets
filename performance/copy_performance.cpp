#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <memory>
#include <time.h>

using namespace std;

struct Base {
  int i;
};

struct Drive : public Base {};

typedef shared_ptr<Base> base_ptr;
typedef shared_ptr<Drive> drive_ptr;

void test_performance() {
  vector<base_ptr> vb, vb1, vb2;
  size_t sz = 10000000; // 10M
  vector<drive_ptr> vd(sz);

  auto t = clock();
  vb.reserve(sz);
  for (size_t i = 0; i < sz; ++i) {
    vb.push_back(vd[i]);
  }
  cout << (double)(clock()-t)/CLOCKS_PER_SEC << endl;

  t = clock();
  vb1.insert(vb1.begin(), vd.begin(), vd.end());
  cout << (double)(clock()-t)/CLOCKS_PER_SEC << endl;

  t = clock();
  vb2.reserve(vb2.size()+vd.size()); // slow without the line
  copy(vd.begin(), vd.end(), back_inserter(vb2));
  cout << (double)(clock()-t)/CLOCKS_PER_SEC << endl;
}

int main(int argc, char* argv[]) {
  auto ptr = make_shared<Base>();
  ptr->i = 10;
  cout << ptr->i << endl;
  
  shared_ptr<Base> ptr2(new Base);
  ptr2->i = 11;
  cout << ptr2->i << endl;

  vector<base_ptr> vb;
  vb.push_back(ptr);
  ptr->i = 100;
  cout << vb.back()->i << endl;

  test_performance();

  return 0;
}
