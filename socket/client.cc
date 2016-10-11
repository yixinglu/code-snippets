
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
  if (ret < 0) sock_test::error("ERROR writing.");
  ret = client.read(buf, buflen);
  std::cout << buf << std::endl;

  return 0;
}
