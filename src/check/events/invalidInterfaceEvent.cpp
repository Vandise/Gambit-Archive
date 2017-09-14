#include "check/events/invalidInterfaceEvent.hpp"

Check::iEvent*
Check::InvalidInterfaceEvent::with(std::vector<std::string> parameters)
{
  this->emitHeader(parameters[0]);
  this->emitError(parameters[1]);

  INITIALIZE_REFERENCES
    DEFINE_REFERENCE(std::string("That ").append(parameters[2]).append(" is define in your module."));
    DEFINE_REFERENCE(std::string("That a pointer to an instance of ").append(parameters[3]).append(" is returned in your module initializer."));
  EMIT_REFERENCES

  return this;
}
