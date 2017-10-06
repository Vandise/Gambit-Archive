#include "check/messageFactory.hpp"

Check::MessageFactory::MessageFactory(CaptureEvents e)
{
  switch(e)
  {
    case INVALID_INTEFACE:
      this->E = new Check::InvalidInterfaceEvent();
      break;
    case ASSIGN_DATATYPE_MISMATCH:
      this->E = new Check::AssignDataTypeMismatch();
      break;
    case USELESS_STATEMENT:
    this->E = new Check::UselessStatement();
      break;
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