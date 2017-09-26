#include "runtime/objectspace/valueObject.hpp"

Runtime::ValueObject::ValueObject(std::string value)
{
  this->stringValue = value;
  this->type = STRING;
}

Runtime::ValueObject::ValueObject(int value)
{
  this->intValue = value;
  this->type = INTEGER;
}

Runtime::iPrimitiveDataType*
Runtime::ValueObject::getValue()
{
  switch(this->type)
  {
    case INTEGER:
      return new Runtime::Primitive(this->intValue);
      break;
    default:
      return new Runtime::Primitive(this->stringValue);
      break;
  }
}