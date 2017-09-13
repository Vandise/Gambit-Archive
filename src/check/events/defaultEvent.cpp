#include "check/events/defaultEvent.hpp"

Check::iEvent*
Check::DefaultEvent::with(std::vector<std::string> parameters)
{
  this->emitHeader(parameters[0]);
  return this;
}
