#ifndef __SOCKET_H__
#define __SOCKET_H__

#include<string>

namespace sock_test {

class Socket {
 public:
  Socket(const char *host, unsigned int port);
  explicit Socket(int sockfd) : sockfd_(sockfd) {}
  ~Socket();

  int write(const char *buf, int len);
  int read(char *buf, int len);

 private:
  int sockfd_;
};

Socket &operator >> (Socket &sock, std::string &str);
Socket &operator << (Socket &sock, const char *str);

extern void error(const char *);

}  // namespace sock_test

#define CHECK(fd, msg)                   \
  do {                                   \
    if ((fd) < 0) sock_test::error(msg); \
  } while (0)

#endif
