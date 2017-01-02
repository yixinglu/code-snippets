#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
  char c[] = "hello world";
  cout << (sizeof(c)/sizeof(c[0])) << endl;
  string str(c);
  cout << str.size() << endl;
  return 0;
}
