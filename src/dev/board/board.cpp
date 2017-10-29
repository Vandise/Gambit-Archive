#include "shared/dev/board.hpp"
#include <iostream>

WsClient::WebSocket::pointer Dev::Board::ws = NULL;

void
Dev::Board::initialize()
{
   Dev::Board::ws = WsClient::WebSocket::from_url("ws://localhost:8080/RookVM");
}

void
Dev::Board::sendMessage(std::string msg)
{
  std::cout << "Sending message " << msg << std::endl;
  Dev::Board::ws->send(msg);
  Dev::Board::ws->poll();
}

void
Dev::Board::terminate()
{
  delete(Dev::Board::ws);
  Dev::Board::ws = NULL;
}