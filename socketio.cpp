#include <thread>
#include "socketio.h"

template<typename T>
SocketIO<T>::SocketIO(const float httpver, const std::string &host, const unsigned port, const Cb &cb) :
  c(std::make_unique<T>(httpver, host, port)), cb(cb), running(1)
{

}

template<typename T>
SocketIO<T>::~SocketIO(void)
{
  kill();
}

template<typename T>
bool SocketIO<T>::connect(void)
{
  return c->connect();
}

template<typename T>
void SocketIO<T>::run(REQ req, const std::string &endp, const std::vector<std::string> &H, const std::string &data, const unsigned waitms, const int expiry)
{
  auto is_running { [&](void) -> bool {
      std::lock_guard<std::mutex> lock(mtx);
      return running;
    }
  };

  const auto init { c->now() };
  while (is_running() && 
    (expiry < 0 || c->template diffpt<std::chrono::milliseconds>(c->now(), init) < (unsigned) expiry))
  {
    c->sendreq(req, endp, H, data);
    c->recvreq();
    cb(c->response());
    std::this_thread::sleep_for(std::chrono::milliseconds(waitms));
  }
}

template<typename T>
void SocketIO<T>::kill(void)
{
  std::lock_guard<std::mutex> lock(mtx);
  running = 0;
}
