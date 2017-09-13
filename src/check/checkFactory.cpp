#include "check/messageFactory.hpp"

Check::MessageFactory::MessageFactory(CaptureEvents e)
{
  switch(e)
  {
    default:
      this->E = new Check::DefaultEvent();
      break;
  }
}

Check::MessageFactory::~MessageFactory()
{
  delete(this->E);
}

Check::iEvent*
Check::MessageFactory::create()
{
  return this->E;
}