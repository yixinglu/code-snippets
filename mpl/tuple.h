#include <type_traits>

namespace mpl {

template <typename... Ts> struct tuple {};

template <typename T, typename... Ts>
struct tuple<T, Ts...> : tuple<Ts...> {
  tuple(T t, Ts... ts) : tuple<Ts...>(ts...), tail(t) {}
  T tail;
};

template <std::size_t, class>
struct element_type_holder;

template <class T, class... Ts>
struct element_type_holder<0, tuple<T, Ts...>> {
  using type = T;
};

template <std::size_t k, class T, class... Ts>
struct element_type_holder<k, tuple<T, Ts...>> {
  using type = typename element_type_holder<k-1, tuple<Ts...>>::type;
};

template <std::size_t k, class... Ts>
using element_type_holder_t = typename element_type_holder<k, tuple<Ts...>>::type;

template <bool predicate, std::size_t k, class...Ts>
using ret_type_t = typename std::enable_if<predicate, element_type_holder_t<k, Ts...>&>::type;

template <std::size_t k, class T, class... Ts>
ret_type_t<k==0, 0, T, Ts...>
get(tuple<T, Ts...> &t) {
  return t.tail;
}

template <std::size_t k, class T, class... Ts>
ret_type_t<k!=0, k, T, Ts...>
get(tuple<T, Ts...> &t) {
  tuple<Ts...> &base = t;
  return get<k-1>(base);
}

}
