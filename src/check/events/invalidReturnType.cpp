#include "check/events/invalidReturnType.hpp"

Check::iEvent*
Check::InvalidReturnType::with(std::vector<std::string> parameters)
{
  this->emitHeader(parameters[0]);

  std::string error = std::string("Method ").append(parameters[1]).append(" expected a returned type of ").append(parameters[2]).append(" but got ")
                      .append(parameters[3]).append(" instead.");

  this->emitError(error);

  emitStackTrace(std::string(parameters[4]), std::string(parameters[5]), std::string(parameters[6]));

  this->emitLine("\n");

  INITIALIZE_REFERENCES
    DEFINE_REFERENCE(std::string("That ").append(parameters[1]).append(" returns an instance of ").append(parameters[3]).append("."));
  EMIT_REFERENCES

  return this;
}