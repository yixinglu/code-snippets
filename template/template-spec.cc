#include <iostream>
#include <type_traits>

template <bool... b>
struct logic_helper {};

template <bool... b>
using all_t = std::is_same<logic_helper<(b || true)...>, logic_helper<b...>>;

struct state_t {};

struct interface_up : state_t {};
struct interface_down : state_t {};
struct loopdown {};

struct builder {
  template <typename... State>
  typename std::enable_if<
      all_t<std::is_base_of<state_t, State>::value...>::value, builder &>::type
  add(State... s) {
    return *this;
  }
};

template <typename X, typename Enable = void>
struct serializer_t {
  static void print() { std::cout << "General" << std::endl; }
};

template <typename X>
struct serializer_t<X, typename std::enable_if<
                           std::is_base_of<state_t, X>::value, void>::type> {
  static void print() { std::cout << "Specialization" << std::endl; }
};

template <>
struct serializer_t<loopdown> {
  static void print() { std::cout << "loop down" << std::endl; }
};

template <typename... Arg>
struct collect {};

template <typename... Arg>
struct serializer_t<collect<Arg...>> {
  static void print() { std::cout << "collect" << std::endl; }
};

template <typename X>
void serialize(X &x) {
  serializer_t<X>::print();
}

int main() {
  interface_up up;
  interface_down down;
  loopdown ld;

  std::cout << std::is_base_of<state_t, decltype(up)>::value << std::endl;
  builder().add(up, down).add(up);
  // builder().add(up, loopdown()); // Error

  serialize(up);
  serialize(ld);
  collect<int, double> c;
  serialize(c);
}
