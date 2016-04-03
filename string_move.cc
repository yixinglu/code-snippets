#include <iostream>
#include <string>

using namespace std;

class String {
 public:
  String(const string &str) : str_(str) {
    cout << "constructor" << endl;
  }

  String(String &&str) : str_(std::move(str.str_)) {
    cout << "rvalue copy constructor" << endl;
  } 

  String(const String &str) : str_(str.str_) {
    cout << "copy constructor" << endl;
  } 

  String &operator=(String &&str) {
    cout << "String &operator=(String &&str)" << endl;
    str_ = std::move(str.str_);
  } 

  String &operator=(const String &str) {
    cout << "String &operator=(const String &str)" << endl;
    str_ = str.str_;
  } 

  string str() const {
    return str_;
  }

 private:
  string str_;
};

String operator +(const String &lhs, const String &rhs) {
  cout << "String operator +(const String &lhs, const String &rhs)" << endl;
  return lhs.str() + rhs.str();
} 

String operator +(String &&lhs, const String &rhs) {
  cout << "String operator +(String &&lhs, const String &rhs)" << endl;
  return lhs.str() + rhs.str();
}

int main(int args, char *argv[]) {
  String l("hello"), r("world"), e("\r\n");
  String result = std::move(l + r + e);   
  String res = result;
  cout << result.str() << endl;
  return 0;
} 
