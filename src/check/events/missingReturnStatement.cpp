#include "check/events/missingReturnStatement.hpp"

Check::iEvent*
Check::MissingReturnStatement::with(std::vector<std::string> parameters)
{

  this->emitHeader(parameters[0]);

  std::string error = std::string("Method ").append(parameters[1]).append(" was expected to return a type of ").append(parameters[2]).append(" but no return statement was specified. ");

  this->emitError(error);

  emitStackTrace(std::string(parameters[4]), std::string(parameters[5]), std::string(parameters[6]));

  this->emitLine("\n");

  INITIALIZE_REFERENCES
    DEFINE_REFERENCE(std::string("That ").append(parameters[1]).append(" has a return statement matching ( =>  ").append(parameters[2]).append(" )."))
    DEFINE_REFERENCE(std::string("That ").append(parameters[1]).append(" was not intended to be Void."))
  EMIT_REFERENCES

  return this;
}