#ifndef __SOCKET_H__
#define __SOCKET_H__

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

extern void error(const char *);

} // namespace sock_test

#endif
