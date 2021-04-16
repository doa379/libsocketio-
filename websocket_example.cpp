#include <iostream>
#include "../libsocket++/socket.h"

static const std::string host0 { "echo.websocket.org" };
static const std::string host1 { "demos.kaazing.com" };
static const unsigned port { 80 };

int main(int argc, char *argv[])
{
  std::string hostname;
  unsigned port_no;
  if (argc != 3)
  {
    std::cerr << "Usage: ./client_example <hostname> <port>\n";
    hostname = host0;
    port_no = port;
  }

  else
  {
    hostname = std::string(argv[1]);
    port_no = std::atoi(argv[2]);
  }

  HttpClient client(1.1);
  if (client.connect(hostname, port_no))
  {
    std::vector<std::string> H {
      //"GET / HTTP/1.1",
      //"GET / HTTP/1.1 101 WebSocket Protocol Handshake",
      //"Host: " + hostname,
      //"Accept: */*",
      "Upgrade: WebSocket",
      "Connection: Upgrade",
      "Sec-WebSocket-Version: 13",
      "Sec-WebSocket-Key: x3JJHMbDL1EzLkh9GBhXDw=="
    };

    if (!client.send_httpreq(GET, "/", H, "Msg"))
    {
      std::cout << client.get_report() << std::endl;
      return 1;
    }
    client.recvreq();
    std::cout << "The response header:\n===================\n";
    std::cout << client.get_header() << std::endl;
    std::cout << "The response body:\n===================\n";
    std::cout << client.get_response() << std::endl;
  }

  else
    std::cout << client.get_report() << std::endl;
  return 0;
}
