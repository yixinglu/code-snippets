#include <stdint.h>

#include <iostream>
#include <variant>

namespace my {

using event_type = uint32_t;

template <class... Types>
struct event_t {
  event_type type;
  std::variant<Types...> value;
};

struct e1_t {
  int a;
};
struct e2_t {
  int b;
};

enum { EVENT_TYPE_E1 = 0, EVENT_TYPE_E2 = 1 };

void dump_event(const event_t<e1_t, e2_t> &e) {
  if (e.type == EVENT_TYPE_E1) {
    std::cout << std::get<e1_t>(e.value).a << std::endl;
  } else if (e.type == EVENT_TYPE_E2) {
    std::cout << std::get<e2_t>(e.value).b << std::endl;
  } else {
    std::cout << "wrong" << std::endl;
  }
}

struct cevt_t {
  event_type type;
  void *value;
};

void dump_cevt(const cevt_t &e) {
  if (e.type == EVENT_TYPE_E1) {
    auto e1 = static_cast<const e1_t *>(e.value);
    std::cout << e1->a << std::endl;
  } else if (e.type == EVENT_TYPE_E2) {
    auto e2 = static_cast<const e2_t *>(e.value);
    std::cout << e2->b << std::endl;
  } else {
    std::cout << "wrong" << std::endl;
  }
}

}  // namespace my

using namespace my;

int main() {
  e1_t e1{0};
  e2_t e2{10};

  event_t<e1_t, e2_t> e;
  e.type = EVENT_TYPE_E1;
  e.value = e1;
  dump_event(e);

  e.type = EVENT_TYPE_E2;
  e.value = e2;
  dump_event(e);

  cevt_t ce;
  ce.type = EVENT_TYPE_E1;
  ce.value = &e1;
  dump_cevt(ce);

  ce.type = EVENT_TYPE_E2;
  ce.value = &e2;
  dump_cevt(ce);
}
