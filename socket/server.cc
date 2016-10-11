
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
  if (ret < 0) sock_test::error("ERROR reading.");
  std::cout << buf << std::endl;
  bzero(buf, buflen);
  snprintf(buf, buflen, "got a msg\n");
  ret = client.write(buf, strlen(buf));
  if (ret < 0) sock_test::error("ERROR writing.");

  return 0;
}
