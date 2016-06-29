#include <iostream>
#include <type_traits>

using namespace std;

template <bool ...b>
struct logic_helper;

template <bool ...b>
using all_t = std::is_same<logic_helper<b...>, logic_helper<(b or true)...>>;

int main() {
  cout << "all_t<true, true>:" << all_t<true, true>::value << endl;
  cout << "all_t<false, true>:" << all_t<false, true>::value << endl;
  return 0;
}
