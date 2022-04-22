#include <type_traits>

namespace mpl {

template <template <typename T> class Predicate, typename Default,
          typename... Rest>
struct get_first_if_impl;

template <template <typename T> class Predicate, typename Default, typename T,
          typename... Rest>
struct get_first_if_impl<Predicate, Default, T, Rest...> {
  using type = typename std::conditional<
      Predicate<T>::value, T,
      typename get_first_if_impl<Predicate, Default, Rest...>::type>::type;
};

template <template <typename T> class Predicate, typename Default>
struct get_first_if_impl<Predicate, Default> {
  using type = Default;
};

template <template <typename T> class Predicate, typename Default,
          typename... T>
using get_first_if = typename get_first_if_impl<Predicate, Default, T...>::type;

}  // namespace mpl
