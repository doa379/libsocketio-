#include "socketio.h"
/*
HttpsClient c(1.1, HOST, 443);
std::vector<std::string> H;

int main(const int argc, const char *argv[])
{
  FILE *fp = fopen("/home/jh/workspace/fxcm/demo_token", "r");
  char TOKEN[64];
  fgets(TOKEN, sizeof TOKEN, fp);
  fclose(fp);
  H = std::vector<std::string>({ "Authorization: Bearer " + std::string(argv[1]) + std::string(TOKEN),
    "Accept: application/json",
    "Content-Type: application/json" });

  c.set_cb([](const std::string &buffer) { std::cout << buffer; });
  c.connect();
  while (1)
  {
    c.sendreq(POST, "/subscribe", H, DATA);
    c.recvreq();
    std::cout << c.get_response() << std::endl;
    sleep(1);
  }

  return 0;
}
*/

template<typename T>
SocketIO<T>::SocketIO(const float httpver, const std::string &host, const unsigned port, const Cb &cb)
{
  c = std::make_unique<T>(httpver, host, port);
  running = 1;
  c->set_cb(cb);
}

template<typename T>
SocketIO<T>::~SocketIO(void)
{
  kill();
  if (th->joinable())
    th->join();
}

template<typename T>
bool SocketIO<T>::connect(void)
{
  return c->connect();
}

template<typename T>
void SocketIO<T>::run(REQUEST req, const std::string &endp, const std::vector<std::string> &H, const std::string &DATA, const unsigned waitms)
{
  th = std::make_unique<std::thread>([&] {
    while (running)
    {
      c->sendreq(req, endp, H, DATA);
      c->recvreq();
    }
  });
}

template<typename T>
void SocketIO<T>::kill(void)
{
  running = 0;
}
