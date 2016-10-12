
#include <iostream>
#include <string.h>
#include "server_socket.h"

using sock_test::ServerSocket;
using sock_test::Socket;

int main() {
  ServerSocket serv_sock(54321);
  Socket client = serv_sock.accept();
  const int buflen = 1024;
  char buf[buflen] = {0};
  int ret = client.read(buf, buflen);
  CHECK(ret, "ERROR reading.");
  std::cout << buf << std::endl;
  bzero(buf, buflen);
  snprintf(buf, buflen, "got a msg\n");
  ret = client.write(buf, strlen(buf));
  CHECK(ret, "ERROR writing.");

  return 0;
}
