#include "index_sequence.h"
#include "get_first_if.h"

using namespace mpl;

template <typename T>
struct is_inconsistent : std::integral_constant<bool, !T::value> {};

struct consistent {
  static constexpr bool value = true;
};

struct inconsistent {
  static constexpr bool value = false;
};

int main() {

  using index_sequence2 = make_sequence_t<2>;
  static_assert(std::is_same<index_sequence2, index_sequence<0, 1>>::value, "");

  using first_t = get_first_if<is_inconsistent, consistent, consistent, inconsistent, consistent>;
  static_assert(std::is_same<inconsistent, first_t>::value, "");

  using default_t = get_first_if<is_inconsistent, consistent>;
  static_assert(std::is_same<consistent, default_t>::value, "");

  return 0;
}