#include "check/events/undefinedMethod.hpp"

Check::iEvent*
Check::UndefinedMethod::with(std::vector<std::string> parameters)
{

  this->emitHeader(parameters[0]);
  this->emitError(std::string("Method ").append(parameters[1]).append(" is not defined."));

  this->emitStackTrace(std::string(parameters[2]), std::string(parameters[3]), std::string(parameters[4]));

  this->emitLine("\n");

  //
  //  TODO:
  //    Pass in runtime and labels for possible method suggestions
  //

  INITIALIZE_REFERENCES
    DEFINE_REFERENCE(std::string("That ").append(parameters[1]).append(" is defined in the current scope."))
  EMIT_REFERENCES

  return this;
}