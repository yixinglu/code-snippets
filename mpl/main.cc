#include <cassert>

#include "get_first_if.h"
#include "index_sequence.h"
#include "tuple.h"

template <typename T>
struct is_inconsistent : std::integral_constant<bool, !T::value> {};

struct consistent {
  static constexpr bool value = true;
};

struct inconsistent {
  static constexpr bool value = false;
};

int main() {
  using index_sequence2 = mpl::make_sequence_t<2>;
  static_assert(std::is_same<index_sequence2, mpl::index_sequence<0, 1>>::value,
                "");

  using first_t = mpl::get_first_if<is_inconsistent, consistent, consistent,
                                    inconsistent, consistent>;
  static_assert(std::is_same<inconsistent, first_t>::value, "");

  using default_t = mpl::get_first_if<is_inconsistent, consistent>;
  static_assert(std::is_same<consistent, default_t>::value, "");

  mpl::tuple<double, int> t{0.1, 2};
  static_assert(
      std::is_same<int, mpl::element_type_holder_t<1, double, int>>::value, "");
  assert(mpl::get<1>(t) == 2);

  return 0;
}
