#include <iostream>
#include "socketio.h"

int main(const int argc, const char *argv[])
{
  if (argc < 2 || !argv[1])
  {
    std::cout << "Argument key expected\n";
    return 1;
  }

  FILE *fp = fopen("/home/jh/workspace/fxcm/demo_token", "r");
  char TOKEN[64];
  fgets(TOKEN, sizeof TOKEN, fp);
  fclose(fp);
  const std::string HOST { "api-demo.fxcm.com" },
    DATA { "{\"pairs\":[\"EUR/USD\",\"AUD/USD\"]}" };
  std::vector<std::string> H { 
    "Authorization: Bearer " + std::string(argv[1]) + std::string(TOKEN),
    "Accept: application/json",
    "Content-Type: application/json"
  };

  auto cb { [](const std::string &buffer) { std::cout << buffer << std::endl; } };
  SocketIO<HttpsClient> c(1.1, HOST, 443, cb);
  c.connect();
  c.run(POST, "/subscribe", H, DATA, 250);
  while (1); 
  return 0;
}
