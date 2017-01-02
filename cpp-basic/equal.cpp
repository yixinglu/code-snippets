#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main() {
  vector<int> v1, v2;
  for (int i = 0; i < 10; ++i) {
    v1.push_back(i);
    v2.push_back(i);
  }

  cout << equal(v1.begin(), v1.end(), v2.begin()) << endl;
  random_shuffle(v1.begin(), v1.end());
  cout << equal(v1.begin(), v1.end(), v2.begin()) << endl;

  return 0;
}
