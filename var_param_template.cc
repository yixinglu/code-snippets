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

struct select_name_t {
};

struct impl_t {
  impl_t() = default;
  impl_t(const select_name_t& data) : _data(data) {}
  select_name_t _data;
};

struct base_t {
  template <typename ...Args>
  base_t(Args&& ...args) : statement_name{} {}
  // base_t(Args&& ...args) : statement_name{std::forward<Args>(args)...} {}
  impl_t statement_name;
};

template <typename U, typename... Ts>
struct test_parameter_park;

int main() {
  cout << "all_t<true, true>:" << all_t<true, true>::value << endl;
  cout << "all_t<false, true>:" << all_t<false, true>::value << endl;
  cout << "test<true, true>():" << test<true, true>().value << endl;
  cout << "test<false, true>():" << test<false, true>().value << endl;

  base_t base(true, 10);
  return 0;
}
