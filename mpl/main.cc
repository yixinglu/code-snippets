#include "index_sequence.h"

using namespace mpl;

int main() {

  using index_sequence2 = make_sequence_t<2>;
  static_assert(std::is_same<index_sequence2, index_sequence<0, 1>>::value, "");

  return 0;
}
