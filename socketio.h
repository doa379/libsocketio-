#pragma once

#include <string>
#include <functional>
#include <memory>
#include <libsocket++/socket.h>
#include <thread>

template<typename T>
class SocketIO
{
  std::unique_ptr<T> c;
  std::unique_ptr<std::thread> th;
  bool running;

public:
  SocketIO(const float, const std::string &, const unsigned, const Cb &);
  ~SocketIO(void);
  bool connect(void);
  void run(REQUEST, const std::string &, const std::vector<std::string> &, const std::string &, const unsigned);
  void kill(void);
};
