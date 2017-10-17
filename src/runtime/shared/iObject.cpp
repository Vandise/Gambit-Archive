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
    //delete(this->klass);
  }
};

Runtime::iStandardClass*
Runtime::iObject::getStandardClass()
{
  return this->klass;
};

void
Runtime::iObject::setStandardClass(Runtime::iStandardClass *klass)
{
  this->klass = klass;
}

std::string
Runtime::iObject::getName()
{
  if (this->klass)
  {
    return this->klass->getName();
  }
  return DEFAULT_CLASS_NAME;
};

Runtime::iStandardClass*
Runtime::iObject::getInstanceVariable(std::string name)
{
  if(this->hasInstanceVariable(name))
  {
    return this->instanceVariables[name];
  }
  // TODO: throw exception
  return nullptr;
}

bool
Runtime::iObject::hasInstanceVariable(std::string name)
{
  if (this->instanceVariables.count(name) > 0)
  {
    return true;
  }
  return false;
}

void
Runtime::iObject::setInstanceVariable(std::string name, Runtime::iStandardClass* value)
{
  // TODO: check datatypes etc.
  this->instanceVariables[name] = value;
}

Runtime::iPrimitiveDataType*
Runtime::iObject::getValue()
{
  // default to void
  return new Runtime::iPrimitiveDataType();
}

std::map<std::string, Runtime::iMethod*>
Runtime::iObject::getMethods()
{
  return this->methods;
}

std::map<std::string, Runtime::iStandardClass*>
Runtime::iObject::getInstanceVariables()
{
  return this->instanceVariables;
}

Runtime::iStandardClass*
Runtime::iObject::clone()
{
  return nullptr;
}


