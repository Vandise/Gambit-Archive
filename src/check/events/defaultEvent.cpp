#include "check/events/defaultEvent.hpp"

Check::iEvent*
Check::DefaultEvent::with(std::vector<std::string> parameters)
{
  this->emitHeader(parameters[0]);
  this->emitError(parameters[1]);
  this->emitReferenceLine();
  this->emitReference(parameters[2], 1);
  return this;
}
