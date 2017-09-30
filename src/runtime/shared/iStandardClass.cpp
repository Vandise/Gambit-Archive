#include "shared/runtime/langRuntime.hpp"
#include "shared/runtime/iStandardClass.hpp"

Runtime::iStandardClass::iStandardClass(std::string name, Runtime::iStandardClass *superClass)
{
  this->name = name;
  this->superClass = superClass;
}

Runtime::iStandardClass::iStandardClass(std::string name)
{
  this->name = name;
  this->klass = Runtime::LangRuntime::objectClass;
  this->superClass = Runtime::LangRuntime::objectClass;
}

Runtime::iStandardClass::~iStandardClass()
{
  std::map<std::string, Runtime::iStandardClass*>::iterator it;
  for (it = this->constants.begin(); it != this->constants.end(); it++)
  {
    if (IT_NOT_INITIAL_CLASSES && it->second != NULL)
    {
      std::cout << "Deleting Class: " << it->second << std::endl;
      delete(it->second);
      it->second = NULL;
    }
  }

  std::map<std::string, Runtime::iStandardClass*>::iterator lt;
  for(lt = this->instanceVariables.begin(); lt != this->instanceVariables.end(); lt++)
  {
    delete(lt->second);
  }

}

Runtime::iStandardClass*
Runtime::iStandardClass::getSuperClass()
{
  return this->superClass;
}

void
Runtime::iStandardClass::setSuperClass(Runtime::iStandardClass *klass)
{
  this->superClass = klass;
}

void
Runtime::iStandardClass::setConstant(std::string name, Runtime::iStandardClass* klass)
{
  this->constants[name] = klass;
}

bool
Runtime::iStandardClass::hasConstant(std::string name)
{
  if(this->constants.count(name) >= 1)
  {
    return true;
  }
  if(this->superClass)
  {
    return this->superClass->hasConstant(name);
  }
  return false;
}

Runtime::iStandardClass*
Runtime::iStandardClass::getConstant(std::string name)
{
  if(this->constants.count(name) >= 1)
  {
    return this->constants[name];
  }
  if(this->superClass)
  {
    return this->superClass->getConstant(name);
  }
  // TODO: create exception
  return nullptr;
}

Runtime::iStandardClass*
Runtime::iStandardClass::newInstance()
{
  return new Runtime::iStandardClass(this);
}

void
Runtime::iStandardClass::newSubclass(std::string name)
{
  Runtime::LangRuntime::objectClass->setConstant(name, (new Runtime::iStandardClass(name, this)) );
}

std::string
Runtime::iStandardClass::getName()
{
  if (this->klass)
  {
    std::cout << this->klass << std::endl;
    return this->klass->getName();
  }
  return this->name;
}