#include <iostream>
#include <memory_resource>   // pmr core types
#include <vector>            // pmr::vector

int main() {
  char buffer[64] = {}; // a small buffer on the stack
  std::fill_n(std::begin(buffer), std::size(buffer) - 1, '_');
  std::cout << buffer << '\n';

  char new_buffer[64] = {}; // a small buffer on the stack
  std::fill_n(std::begin(new_buffer), std::size(new_buffer) - 1, '_');
  std::cout << new_buffer << '\n';

  std::pmr::monotonic_buffer_resource pool{std::data(buffer), std::size(buffer)};

  std::pmr::vector<char> vec{ &pool };
  for (char ch = 'a'; ch <= 'z'; ++ch)
    vec.push_back(ch);

  std::cout << buffer << '\n';

  auto new_vec = reinterpret_cast<std::pmr::vector<char> *>(buffer);
  // std::cout << (*new_vec)[2] << std::endl;;

  std::pmr::vector<char> vec2 {&pool};
  std::cout << vec2[2] << std::endl;
}
