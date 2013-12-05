#include "udp.h"
#include <stdlib.h>

extern uv_buf_t on_alloc(uv_handle_t* handle, size_t suggested_size);

void udp_recv_cb(uv_udp_t* handle, ssize_t nread, uv_buf_t buf,
                 struct sockaddr* addr, unsigned flags) {
  struct sockaddr_in* pAddr_in = (struct sockaddr_in*)addr;
  Address address;

  if (pAddr_in->sin_family == AF_INET) {
    // addrstr is a pointer to static buffer, no need to free
//    char* addrstr = inet_ntoa(pAddr_in->sin_addr);
//    if (addrstr)
//      address.host = std::string(addrstr);
//    else {
//      // TODO: warn?
//    }
//    address.port = ntohs(pAddr_in->sin_port);
  }

  UdpSocket* pSocket = reinterpret_cast<UdpSocket*>(handle);
  pSocket->pApplication->onMessage(address, buf.base, nread, flags);
}

uv_udp_t* createUdpServer(
  const std::vector<std::string>& multicastAddresses,
  const std::string& host, int port, UdpApplication* pApp) {

  UdpSocket* pSocket = new UdpSocket();
  pSocket->pApplication = pApp;
  if (uv_udp_init(uv_default_loop(), &pSocket->socket))
    return NULL;
  struct sockaddr_in address = uv_ip4_addr(host.c_str(), port);
  if (uv_udp_bind(&pSocket->socket, address, 0)) {
    return NULL;
  }
  for (std::vector<std::string>::const_iterator it = multicastAddresses.begin();
       it != multicastAddresses.end();
       it++) {
    if (uv_udp_set_membership(&pSocket->socket, it->c_str(), host.c_str(), UV_JOIN_GROUP)) {
      // TODO: Log
    }
  }
  // TODO: Free on_alloc
  if (uv_udp_recv_start(&pSocket->socket, &on_alloc, &udp_recv_cb)) {
    // TODO: Clean up and return NULL
  }
  return &pSocket->socket;
}