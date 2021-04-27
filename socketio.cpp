#include "socketio.h"

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
      cb(c->get_response());
    }
  });
}

template<typename T>
void SocketIO<T>::kill(void)
{
  running = 0;
}
