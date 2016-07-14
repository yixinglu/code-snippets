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

template <std::size_t k, class T, class... Ts>
typename std::enable_if<k == 0, element_type_holder_t<0, T, Ts...>&>::type
get(tuple<T, Ts...> &t) {
  return t.tail;
}

template <std::size_t k, class T, class... Ts>
typename std::enable_if<k!=0, element_type_holder_t<k, T, Ts...>&>::type
get(tuple<T, Ts...> &t) {
  tuple<Ts...> &base = t;
  return get<k-1>(base);
}

}
