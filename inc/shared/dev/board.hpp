#ifndef __DEVBOARD_HPP
#define __DEVBOARD_HPP 1

#include <string>
#include <sstream>
#include "shared/config.hpp"
#include "shared/dev/wsclient.hpp"

using WsClient::WebSocket;

namespace Runtime
{
  class iStandardClass;
}

namespace Dev
{

  class Board
  {

    public:
      static WebSocket::pointer ws;
      static void initialize();
      static void terminate();
      static void sendMessage(std::string msg);
      static std::string formatClassMsg(Runtime::iStandardClass* klass);
  };

}

#endif