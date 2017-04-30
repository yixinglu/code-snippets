
#include <iostream>
#include <string.h>
#include "socket.h"

using sock_test::Socket;

int main() {
  Socket client("localhost", 54321);
  const int buflen = 1024;
  char buf[buflen] = {0};
  snprintf(buf, buflen, "hello socket!\n");
  int ret = client.write(buf, strlen(buf));
  CHECK(ret, "ERROR writing.");
  ret = client.read(buf, buflen);
  CHECK(ret, "ERROR reading.");
  std::cout << buf << std::endl;

  return 0;
}
