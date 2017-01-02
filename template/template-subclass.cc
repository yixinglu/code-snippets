#include <iostream>

namespace test1 {
template <typename Sub>
struct Base {
  using sub_type = Sub;

  // ERROR: incomplete sub_type
  // auto sub() -> decltype(sub_type{}) { return {sub_type{}}; }
};

struct Sub : Base<Sub> {};
}  // namespace test1

namespace test2 {
template <typename Sub>
struct Base : Sub::_base_t {
  auto base() -> Base<Sub> {
    std::cout << "base" << std::endl;
    return {};
  }
};

struct Sub {
  struct _base_t {
    auto sub() -> Base<Sub> {
      std::cout << "sub" << std::endl;
      return {};
    }
  };
};
}  // namespace test2

int main() {
  // test1::Sub().sub();
  test2::Base<test2::Sub> sub2;
  sub2.sub().base();

  return 0;
}
