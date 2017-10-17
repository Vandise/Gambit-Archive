#include "check/events/undefinedVariable.hpp"

Check::iEvent*
Check::UndefinedVariable::with(std::vector<std::string> parameters)
{

  this->emitHeader(parameters[0]);
  this->emitError(std::string("Variable ").append(parameters[1]).append(" is not defined."));

  this->emitStackTrace(std::string(parameters[2]), std::string(parameters[3]), std::string(parameters[4]));

  this->emitLine("\n");

  INITIALIZE_REFERENCES
    DEFINE_REFERENCE(std::string("That ").append(parameters[1]).append(" is defined in the current scope."))
  EMIT_REFERENCES

  return this;
}