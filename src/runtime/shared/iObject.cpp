#include "shared/runtime/iObject.hpp"
#include "shared/runtime/iStandardClass.hpp"

Runtime::iObject::iObject(Runtime::iStandardClass *klass)
{
  this->klass = klass;
};

Runtime::iObject::iObject(std::string name)
{
  // does nothing as we don't have a runtime setup/booted yet
};

Runtime::iObject::~iObject()
{
  if (this->klass != nullptr)
  {
    delete(this->klass);
  }
};

Runtime::iStandardClass*
Runtime::iObject::getStandardClass()
{
  return this->klass;
};

std::string
Runtime::iObject::getName()
{
  if (this->klass)
  {
    return this->klass->getName();
  }
  return DEFAULT_CLASS_NAME;
};

Runtime::iPrimitiveDataType*
Runtime::iObject::getValue()
{
  // default to void
  return new Runtime::iPrimitiveDataType();
};