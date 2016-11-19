#include <stdio.h>

void discardAndNewline(int /*arr*/[]) { printf("\n"); }

struct Event {};

struct EventStream {
  int index;
  EventStream(int i) : index(i){};
};

using IE = EventStream;

struct InputT {
  template <typename... EVENTSTREAM>
  InputT(EVENTSTREAM... es) {
    int dummy[sizeof...(es)]{(printf("%d, ", es.index), 0)...};
    discardAndNewline(dummy);
  };
};

struct State {
  template <typename... STATES>
  State(STATES... args) {
    int dummy[sizeof...(args)]{(printf("%d, ", args), 0)...};
    discardAndNewline(dummy);
  };
  template <typename... EVENTSTREAM>
  auto input(EVENTSTREAM... eventst) -> decltype(InputT()) {
    return InputT(eventst...);
  };
};

struct FSMT {
  template <typename... STATES>
  auto state(STATES... st) -> decltype(State()) {
    return State(st...);
  };
};

FSMT FSM() { return FSMT(); }

int main(int argc, char **argv) {
  enum status { P2P, DOWN, WAITING, DR, BACKUP, DRother, LOOPBACK, Election };

  FSM()
      .state(P2P, DOWN, WAITING, DR, BACKUP, DRother, LOOPBACK, Election)
      .input(IE(1), IE(2), IE(3));

  return 0;
}
