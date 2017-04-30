#ifndef __SERVER_SOCKET_H__
#define __SERVER_SOCKET_H__

#include "socket.h"

namespace sock_test {

class ServerSocket {
 public:
  explicit ServerSocket(unsigned int port);
  ~ServerSocket();

  Socket accept();

 private:
  int sockfd_;
};

}  // namespace sock_test

#endif
