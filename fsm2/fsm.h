#include <algorithm>
#include <string>
#include <vector>

namespace fsm {

template <typename T>
struct Event {
  using state_type = T;
  const std::string &name;
  std::vector<T> src;
  T dst;
};

template<typename Event>
struct FSM {
  using state_type = typename Event::state_type;
  state_type current_state;
  std::vector<Event> events;

  FSM(state_type state) : current_state(state) {}

  FSM &addEvent(const Event &e) {
    events.push_back(e);
    return *this;
  }

  void apply(const std::string &event_name) {
    auto iter = std::find_if(events.begin(), events.end(), [&](const Event &e) {
        return e.name == event_name;
      });
    if (iter != events.end()) {
      auto it = std::find_if(iter->src.begin(), iter->src.end(), [&](const state_type &s){
          return s == current_state;
        });
      if (it != iter->src.end()) {
        current_state = iter->dst;
      }
    }
  }
};

} // namespace fsm
