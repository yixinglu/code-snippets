
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "server_socket.h"

namespace sock_test {

ServerSocket::ServerSocket(unsigned int port) {
  sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd_ < 0) {
    error("ERROR opening socket.");
  }
  sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port);
  if (bind(sockfd_, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
    error("ERROR on binding.");
  }
  listen(sockfd_, 5);
}

ServerSocket::~ServerSocket() { close(sockfd_); }

Socket ServerSocket::accept() {
  struct sockaddr_in cli_addr;
  socklen_t cli_len = sizeof(cli_addr);
  int newsockfd = ::accept(sockfd_, (struct sockaddr*)&cli_addr, &cli_len);
  if (newsockfd < 0) { error("ERROR on accept.");}
  return Socket(newsockfd);
}

} // namespace sock_test
