
#include <cassert>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

[[deprecated]] bool ParseDatetime(const string &str, std::tm *tm) {
  std::istringstream ss(str);
  ss >> std::get_time(tm, "%Y-%m-%dT%H:%M:%S");
  if (ss.fail()) {
    ss.clear();
    ss.str(str);
    ss >> std::get_time(tm, "%Y-%m-%d %H:%M:%S");
    if (ss.fail()) {
      return false;
    }
  }
  return true;
}

int main() {
  std::tm tm;
  assert(ParseDatetime("2021-07-21T02:29:43", &tm));
  assert(ParseDatetime("2021-07-21 02:29:43", &tm));
  assert(!ParseDatetime("2021-07-21_02:29:43", &tm));

  return 0;
}
