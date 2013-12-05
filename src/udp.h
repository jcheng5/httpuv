#ifndef UDP_H
#define UDP_H

#include <vector>

#include <Rcpp.h>
#undef Realloc
// Also need to undefine the Free macro
#undef Free
#include <uv.h>

#include "http.h"

class UdpApplication {
public:
  virtual ~UdpApplication() {}
  virtual void onMessage(const Address& addr,
                         const char* data, size_t len,
                         unsigned flags) = 0;
};

struct UdpSocket {
  uv_udp_t socket;
  UdpApplication* pApplication;
};

void udp_recv_cb(uv_udp_t* handle, ssize_t nread, uv_buf_t buf,
                 struct sockaddr* addr, unsigned flags);

uv_udp_t* createUdpServer(
  const std::vector<std::string>& multicastAddresses,
  const std::string& host, int port, UdpApplication* pApp);

#endif // UDP_H