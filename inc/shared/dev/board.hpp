#ifndef __DEVBOARD_HPP
#define __DEVBOARD_HPP 1

#include "shared/dev/wsclient.hpp"

using WsClient::WebSocket;

namespace Dev
{

  class Board
  {

    public:
      static WebSocket::pointer ws;
      static void initialize();
      static void terminate();
  };

}

#endif