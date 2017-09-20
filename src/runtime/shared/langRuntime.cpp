#include "shared/runtime/langRuntime.hpp"
#include "runtime/objectspace/standardClass.hpp"

Runtime::iStandardClass* Runtime::LangRuntime::klass;
Runtime::iStandardClass* Runtime::LangRuntime::objectClass;
Runtime::iObject* Runtime::LangRuntime::mainObject;

void
Runtime::LangRuntime::bootstrap()
{
  // A Klass inherits from a Klass - top level object
  Runtime::LangRuntime::klass = new Runtime::StandardClass("Klass");
  Runtime::LangRuntime::klass->setSuperClass(Runtime::LangRuntime::klass);

  // Object inherits from Klass
  Runtime::LangRuntime::objectClass = new Runtime::StandardClass("Object", Runtime::LangRuntime::klass);

  // Main object provides the user access to the object hierarchy 
  Runtime::LangRuntime::mainObject = new Runtime::iObject();
  Runtime::LangRuntime::mainObject->setStandardClass(Runtime::LangRuntime::objectClass);

  // Define our object hierarchy available to the user
  //  Klass
  //    -> Object
  Runtime::LangRuntime::objectClass->setConstant("Object", Runtime::LangRuntime::objectClass);
  Runtime::LangRuntime::objectClass->setConstant("Klass", Runtime::LangRuntime::klass);

}

void
Runtime::LangRuntime::destroy()
{
  delete(Runtime::LangRuntime::klass);
  delete(Runtime::LangRuntime::objectClass);
  delete(Runtime::LangRuntime::mainObject);
}