#include <iostream>
#include <type_traits>

using namespace std;

template <bool ...b>
struct logic_helper;

template <bool ...b>
using all_t = std::is_same<logic_helper<b...>, logic_helper<(b or true)...>>;

template <bool ...b>
auto test() -> all_t<b...> {
  return {};
}

int main() {
  cout << "all_t<true, true>:" << all_t<true, true>::value << endl;
  cout << "all_t<false, true>:" << all_t<false, true>::value << endl;
  cout << "test<true, true>():" << test<true, true>().value << endl;
  cout << "test<false, true>():" << test<false, true>().value << endl;
  return 0;
}
