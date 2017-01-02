#include <algorithm>
#include <cstdlib> 
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

const int THRESHOLD = 100;

void sum(const vector<int> &data) {
  double start = (double)clock() / CLOCKS_PER_SEC;

  long sum = 0;
  for (auto it=data.begin(); it != data.end();++it) {
    if (*it >= THRESHOLD) sum += *it;
  }

  double end = (double)clock() / CLOCKS_PER_SEC;
  cout << "sum " << (end - start) << "s, sum=" <<sum << endl;
}

void sum_foreach(const vector<int> &data) {
  double start = (double)clock() / CLOCKS_PER_SEC;

  long sum = 0;
  for_each(data.begin(), data.end(), [&](int val) {
    if (val >= THRESHOLD) sum += val;
  }); 

  double end = (double)clock() / CLOCKS_PER_SEC;
  cout << "sum_foreach " << (end - start) << "s, sum=" << sum << endl;
}

void sum2(const vector<int> &data) { 
  double start = (double)clock() / CLOCKS_PER_SEC;

  long sum = 0;
  for (auto it=data.begin(); it!=data.end();++it) {
    int cmp=(*it-THRESHOLD) >> 31;
    sum += ~cmp & *it;
  }

  double end = (double)clock() / CLOCKS_PER_SEC;
  cout << "sum2 " << (end - start) << "s, sum=" << sum << endl;
}

void sum2_foreach(const vector<int> &data) { 
  double start = (double)clock() / CLOCKS_PER_SEC;

  long sum = 0;
  for_each(data.begin(), data.end(), [&](int val) {
    int cmp = (val - THRESHOLD) >> 31;
    sum += ~cmp & val;
  }); 

  double end = (double)clock() / CLOCKS_PER_SEC;
  cout << "sum2_foreach " << (end - start) << "s, sum=" << sum << endl;
}

int main(int argc, char *argv[]) {
  
  const size_t NUM = 16 * 1024 * 1024; 
  
  vector<int> data(NUM);
  for_each(data.begin(), data.end(), [](int &val) { val = rand(); });
  
  sum(data);
  sum2(data);
  sum_foreach(data);
  sum2_foreach(data);

  sort(data.begin(), data.end());

  sum(data);
  sum2(data); 
  sum_foreach(data);
  sum2_foreach(data);

  return 0;
}
