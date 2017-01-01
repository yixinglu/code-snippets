
template <typename Sub>
struct Base {
  using sub_type = Sub;

  // ERROR: incomplete sub_type
  auto sub() -> decltype(sub_type{}) { return {sub_type{}}; }
};

struct Sub : Base<Sub> {};

int main() {
  Sub().sub();

  return 0;
}
