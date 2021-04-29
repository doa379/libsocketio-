#pragma once

#include <string>
#include <functional>
#include <memory>
#include <libsocket++/socket.h>
#include <mutex>

template<typename T>
class SocketIO
{
  std::unique_ptr<T> c;
  Cb cb;
  bool running;
  std::mutex mtx;

public:
  SocketIO(const float, const std::string &, const unsigned, const Cb &);
  ~SocketIO(void);
  bool connect(void);
  void run(REQUEST, const std::string &, const std::vector<std::string> &, const std::string &, const unsigned, const int = -1);
  void kill(void);
};

template class SocketIO<HttpClient>;
template class SocketIO<HttpsClient>;
