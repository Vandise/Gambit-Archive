#include "check/events/assignDataTypeMismatch.hpp"

Check::iEvent*
Check::AssignDataTypeMismatch::with(std::vector<std::string> parameters)
{
  this->emitHeader(parameters[0]);

  std::string error = std::string("Variable ").append(parameters[1]).append(" is an instance of Class ").append(parameters[2]).append(". ")
                      .append(" You assigned a value of Class ").append(parameters[3]).append(".");

  this->emitError(error);
  //this->emitTrace();

  //this->emitLine("TODO file trace: " + std::string(parameters[4] + " :: " + parameters[5] + " - " + parameters[6]));

  emitStackTrace(std::string(parameters[4]), std::string(parameters[5]), std::string(parameters[6]));

  this->emitLine("\n");

  INITIALIZE_REFERENCES
    DEFINE_REFERENCE(std::string("That ").append(parameters[1]).append(" is an instance of ").append(parameters[3]).append("."));
    DEFINE_REFERENCE(std::string("That you have casted Class ").append(parameters[3]).append(" to an instance of Class ").append(parameters[2]).append("."));
  EMIT_REFERENCES

  return this;
}