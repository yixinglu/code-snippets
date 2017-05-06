#include <iostream>
#include <variant>
#include <stdint.h>

namespace my {

using event_type = uint32_t;

template <class... Types>
struct event_t {
  event_type type;
  std::variant<Types...> value;
};

struct e1_t { int a; };
struct e2_t { int b; };

enum {
  EVENT_TYPE_E1 = 0,
  EVENT_TYPE_E2 = 1
};

void dump_event(const event_t<e1_t, e2_t> &e) {
  if (e.type == EVENT_TYPE_E1) {
    std::cout << std::get<e1_t>(e.value).a << std::endl;
  } else if (e.type == EVENT_TYPE_E2) {
    std::cout << std::get<e2_t>(e.value).b << std::endl;
  } else {
    std::cout << "wrong" << std::endl;
  }
}

}

using namespace my;
using namespace std;

int main() {
  e1_t e1{0};
  e2_t e2{10};

  event_t<e1_t, e2_t> e;
  e.type = 0;
  e.value = e1;

  dump_event(e);

  e.type = 1;
  e.value = e2;
  dump_event(e);
}
