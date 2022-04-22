#include <iostream>
#include <type_traits>

using namespace std;

template <bool... b>
struct logic_helper;

template <bool... b>
using all_t = std::is_same<logic_helper<b...>, logic_helper<(b or true)...>>;

template <bool... b>
auto test() -> all_t<b...> {
  return {};
}

struct select_name_t {};

struct impl_t {
  impl_t() = default;
  impl_t(const select_name_t& data) : _data(data) {}
  select_name_t _data;
};

struct base_t {
  template <typename... Args>
  base_t(Args&&... args) : statement_name{} {}
  // base_t(Args&& ...args) : statement_name{std::forward<Args>(args)...} {}
  impl_t statement_name;
};

template <typename U, typename... Ts>
struct test_parameter_park;

template <template <class...> class Fn>
struct meta_quote {
  template <typename... Ts>
  using apply = Fn<Ts...>;
};

template <typename T>
struct meta_always {
  template <typename... Ts>
  using apply = T;
};

template <typename...>
struct typelist;

template <typename T>
struct transform;

template <typename... Ts>
struct transform<typelist<Ts...>> {
  static constexpr bool value = true;
};

int main() {
  cout << "all_t<true, true>:" << all_t<true, true>::value << endl;
  cout << "all_t<false, true>:" << all_t<false, true>::value << endl;
  cout << "test<true, true>():" << test<true, true>().value << endl;
  cout << "test<false, true>():" << test<false, true>().value << endl;

  base_t base(true, 10);

  cout
      << "meta_quote<meta_always> type:"
      << std::is_same<meta_quote<meta_always>::apply<int>::apply<double, float>,
                      int>::value
      << endl;
  // meta_quote<meta_always>::apply<int, double>::apply<double, float> t; //
  // error

  cout << "transform value:" << transform<typelist<int, double>>::value << endl;
  // cout << "transform value:" << transform<int, double>::value << endl; //
  // error

  return 0;
}
