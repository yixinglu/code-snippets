
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "socket.h"

namespace sock_test {

void error(const char *msg) {
  perror(msg);
  exit(1);
}

Socket::Socket(const char *host, unsigned int port) {
  sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
  CHECK(sockfd_, "ERROR opening socket.");

  hostent *server = gethostbyname(host);
  if (server == NULL) { error("ERROR no such host."); }
  sockaddr_in serv_addr;
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(port);

  CHECK(connect(sockfd_, (sockaddr *)&serv_addr, sizeof(serv_addr)), "ERROR connecting.");
}

Socket::~Socket() { close(sockfd_); }

int Socket::write(const char *buf, int len) {
  return ::write(sockfd_, buf, len);
}

int Socket::read(char *buf, int len) {
  bzero(buf, len);
  return ::read(sockfd_, buf, len);
}

} // namespace sock_test
