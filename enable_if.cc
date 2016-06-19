#include <type_traits>
#include <iostream>

using namespace std;

template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type
is_odd(T i) {
  return bool(i%2);
}

template <typename T,
	  typename = typename std::enable_if<std::is_integral<T>::value>::type
	>
bool is_even(T i) {
	return !is_odd(i);
}

// -----------------
template<typename T>
using type = typename std::enable_if<std::is_integral<T>::value>::type;

// -----------------
template <bool, typename R=void> 
struct Test {};

template<typename R>
struct Test<true, R> {
 using type = R;
};

template <typename T>
typename Test<std::is_integral<T>::value, void>::type
test(T i) {
  cout << i << endl;
  // return i;
}

// -----------------

template <typename C, typename Enable=void>
struct run_check { };

template <typename C>
struct run_check<C,
                 typename std::enable_if<std::is_integral<C>::value>::type
                 >
{
  using type = C;
};

template <typename C>
typename run_check<C>::type test_run_check(C c) {
  cout << c << endl;
  return c;
}

template <typename C>
struct run_check<C, float> {
  using type = float;
};

template <typename C>
struct run_check<C, void> {
  using type = void;
};

template <typename C>
typename run_check<C>::type test_run_check2(C c) {
  cout << "test_run_check2: " << c << endl;
}
// -----------------
int main() {

  cout << "5 is odd:" << is_odd(5) << endl;
  // cout << "5.0 is odd:" << is_odd(5.0) << endl;
  cout << "5 is even:" << is_even(5) << endl;
  // cout << "5.0 is even:" << is_even(5.0) << endl;

  Test<true, int>::type i;
  // Test<false, int>::type i;
  test(5);

  // test_run_check(5);
  // test_run_check(5.0);
  // test_run_check2(5);
  test_run_check2(5.0); 

  return 0;
}
