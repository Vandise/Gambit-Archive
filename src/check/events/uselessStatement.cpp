#include "check/events/uselessStatement.hpp"

Check::iEvent*
Check::UselessStatement::with(std::vector<std::string> parameters)
{
  this->emitHeader(parameters[0]);


  std::string error = std::string("Expression regarding class ").append(parameters[1]).append(" (").append(parameters[2]).append(") ").append(" is not used.");

  this->emitError(error);

  this->emitStackTrace(std::string(parameters[3]), std::string(parameters[4]), std::string(parameters[5]));

  this->emitLine("\n");

  INITIALIZE_REFERENCES
    DEFINE_REFERENCE(std::string("That ").append(parameters[1]).append(" (").append(parameters[2]).append(") ").append(" is used in the current scope."))
    DEFINE_REFERENCE(std::string("That you have removed or commented out ").append(parameters[1]).append(" (").append(parameters[2]).append(") ").append(" on line: ").append(parameters[4]).append("."))
  EMIT_REFERENCES

  return this;
}