#include <algorithm>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <stdlib.h>

using namespace std;
using namespace std::tr1;

struct Bar {
  int id;
  double data;
};

ostream& operator << (ostream& out, const Bar& bar) {
  out << "[" << bar.id << ", " << bar.data << "]";
  return out;
}

void eliminate_duplication(vector<Bar>& bars) {
  vector<Bar> tmp;
  tmp.swap(bars);
  bars.reserve(tmp.size());
  unordered_set<int> ids;
  for_each(tmp.begin(), tmp.end(), [&](const Bar& bar) {
    if (ids.insert(bar.id).second) {
      bars.push_back(bar);
    } 
  }); 
}

void init_vector(vector<Bar>& bars, int sz) {
  bars.resize(sz);
  for (size_t i = 0; i < sz; ++i) {
    bars[i].id = rand() % 100;
    bars[i].data = 0.0;
  }
}

void print_bar_vector(const vector<Bar>& bars) {
  for_each(bars.begin(), bars.end(), [&](const Bar& bar) {
    cout << bar << " ";
  });
  cout << endl;
}

int main(int argc, char* argv[]) {
  if (argc != 2) return 1;
  
  stringstream ss(argv[1]);
  int sz = 0;
  ss >> sz;
  if (sz <= 0) return 1;

  vector<Bar> bars;
  init_vector(bars, sz);
  print_bar_vector(bars);
  eliminate_duplication(bars);
  print_bar_vector(bars);

  return 0;
}
