#include <iostream>
#include "fsm.h"

using namespace std;

int main() {
  fsm::Event<string> e1{"warn", {"green"}, "yellow"};
  fsm::Event<string> e2{"panic", {"yellow"}, "red"};
  fsm::FSM<fsm::Event<string>> sm("green");
  sm.addEvent(e1).addEvent(e2);
  sm.apply("warn");
  sm.apply("panic");
  cout << sm.current_state << endl;
}
