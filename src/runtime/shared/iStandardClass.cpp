#include "shared/runtime/langRuntime.hpp"
#include "shared/runtime/iStandardClass.hpp"

Runtime::iStandardClass::iStandardClass( Runtime::iStandardClass* klass ) : Runtime::iObject(klass)
{
  this->superClass = klass->getSuperClass();
  this->name = klass->getName();
}

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
      //std::cout << "Deleting Class: " << it->second << std::endl;
      delete(it->second);
      it->second = NULL;
    }
  }

  std::map<std::string, Runtime::iStandardClass*>::iterator lt;
  for(lt = this->instanceVariables.begin(); lt != this->instanceVariables.end(); lt++)
  {
    delete(lt->second);
  }

  std::map<std::string, Runtime::iMethod*>::iterator methodIt;
  for(methodIt = this->methods.begin(); methodIt != this->methods.end(); methodIt++)
  {
    delete(methodIt->second);
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
  if (this->name.size() > 0)
  {
    return this->name;
  }
  return this->klass->getName();
}

Runtime::iMethod*
Runtime::iStandardClass::lookup(std::string name)
{
  if(this->methods.count(name) >= 1)
  {
    return this->methods[name];
  }

  if(this->superClass != nullptr)
  {
    return this->superClass->lookup(name);
  }

  // TODO:
  //    create exception for undefined method, parser will catch this
  return nullptr;
}

bool
Runtime::iStandardClass::hasMethod(std::string name)
{
  if(this->methods.count(name) >= 1)
  {
    return true;
  }

  if(this->superClass != nullptr)
  {
    // Klass has no methods
    if (this->superClass->getName() == this->getName())
    {
      return false;
    }
    return superClass->hasMethod(name);
  }
  return false;
}

void
Runtime::iStandardClass::addMethod(std::string name, Runtime::iMethod *method)
{
  std::string thisName = this->getName();
  std::string identifier = thisName.append("_").append(method->generateMethodName(name));
  this->methods[identifier] = method;
}


Runtime::iStandardClass*
Runtime::iStandardClass::clone()
{
  //std::cout << "Cloning iStandardClass" << std::endl;
  Runtime::iStandardClass* clone = new Runtime::iStandardClass( this->getName(), this->getSuperClass() );

  std::map<std::string, Runtime::iMethod*>::iterator im;
  for( im = this->methods.begin(); im != this->methods.end(); im++ )
  {
    clone->addMethod( im->first, im->second );
  }

  std::map<std::string, Runtime::iStandardClass*>::iterator iv;
  for( iv = this->instanceVariables.begin(); iv != this->instanceVariables.end(); iv++ )
  {
    clone->setInstanceVariable( iv->first, iv->second->clone() );
  }

  return clone;
}
