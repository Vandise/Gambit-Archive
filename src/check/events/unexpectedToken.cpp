#include "check/events/unexpectedToken.hpp"

Check::iEvent*
Check::UnexpectedToken::with(std::vector<std::string> parameters)
{

  this->emitHeader(parameters[0]);
  this->emitError(parameters[1]);

  this->emitStackTrace(std::string(parameters[2]), std::string(parameters[3]), std::string(parameters[4]));

  this->emitLine("\n");
/*
  INITIALIZE_REFERENCES
    DEFINE_REFERENCE(std::string("That ").append(parameters[1]).append(" (").append(parameters[2]).append(") ").append(" is used in the current scope."))
    DEFINE_REFERENCE(std::string("That you have removed or commented out ").append(parameters[1]).append(" (").append(parameters[2]).append(") ").append(" on line: ").append(parameters[4]).append("."))
  EMIT_REFERENCES
*/
  return this;
}