#include "shared/dev/board.hpp"

WsClient::WebSocket::pointer Dev::Board::ws = NULL;

void
Dev::Board::initialize()
{
   Dev::Board::ws = WsClient::WebSocket::from_url("ws://localhost:8080/rookVM");
}

void
Dev::Board::terminate()
{
  delete(Dev::Board::ws);
  Dev::Board::ws = NULL;
}