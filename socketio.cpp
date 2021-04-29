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
  if (th->joinable())
    th->join();
}

template<typename T>
bool SocketIO<T>::connect(void)
{
  return c->connect();
}

template<typename T>
void SocketIO<T>::run(REQUEST req, const std::string &endp, const std::vector<std::string> &H, const std::string &data, const unsigned waitms, const int expiry)
{
  auto is_running { [&](void) -> bool {
      std::lock_guard<std::mutex> lock(mtx);
      return running;
    }
  };

  th = std::make_unique<std::thread>([&] {
    while (is_running() && 1/*time_now - time_init < expiry*/)
    {
      c->sendreq(req, endp, H, data);
      c->recvreq();
      cb(c->get_response());
      std::this_thread::sleep_for(std::chrono::milliseconds(waitms));
    }
  });
}

template<typename T>
void SocketIO<T>::kill(void)
{
  std::lock_guard<std::mutex> lock(mtx);
  running = 0;
}
