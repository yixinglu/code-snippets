#include <iostream>

namespace test1 {
template <typename Sub>
struct Base {
  using sub_type = Sub;

#if 0
  // ERROR: incomplete sub_type
  auto sub() -> decltype(sub_type{}) { return {sub_type{}}; }
#endif
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
#if 0
  auto base2() -> decltype(Base<Sub>{}) {
    std::cout << "base2" << std::endl;
    return {};
  }
#endif
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

namespace test3 {
#if 0
struct Base {
  template <typename T>
  virtual Base& fun(T t) {
    return *this;
  }
};

struct Sub : Base {
  template <typename T>
  Sub& fun(T t) override {
    Base::fun<T>(t);
    return *this;
  }
}
#endif
}  // namespace test3

int main() {
  // test1::Sub().sub();
  test2::Base<test2::Sub> sub2;
  // sub2.sub().base().base2();
  sub2.sub().base();

  // test3::Sub sub3;
  // sub3.fun(5);

  return 0;
}
