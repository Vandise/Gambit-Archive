#include "shared/dev/board.hpp"
#include <iostream>

WsClient::WebSocket::pointer Dev::Board::ws = NULL;

void
Dev::Board::initialize()
{
  if (_DEBUG)
  {
    Dev::Board::ws = WsClient::WebSocket::from_url("ws://localhost:8080/RookVM");
  }
}

void
Dev::Board::sendMessage(std::string msg)
{
  if (_DEBUG && Dev::Board::ws != NULL)
  {
    if (Dev::Board::ws->getReadyState() == WsClient::WebSocket::OPEN)
    {
      Dev::Board::ws->send(msg);
      Dev::Board::ws->poll();
    }
  }
}

void
Dev::Board::terminate()
{
  if (_DEBUG)
  {
    delete(Dev::Board::ws);
    Dev::Board::ws = NULL;
  }
}