#include <type_traits>

namespace mpl {

template <std::size_t... Ints>
struct index_sequence {};

template <typename T, std::size_t N>
struct make_sequence_impl;

template <std::size_t N, std::size_t... Ints>
struct make_sequence_impl<index_sequence<Ints...>, N> {
  using type = typename make_sequence_impl<index_sequence<Ints..., sizeof...(Ints)>, N-1>::type;
};

template <std::size_t... Ints>
struct make_sequence_impl<index_sequence<Ints...>, 0> {
  using type = index_sequence<Ints...>;
};

template <std::size_t N>
using make_sequence_t = typename make_sequence_impl<index_sequence<>, N>::type;

}
