#include "ext/loader/extensionLoader.hpp"

Extensions::ExtensionLoader::ExtensionLoader(std::string module)
{
  this->moduleName = "./lib/" + module + ".so";
  this->handle = dlopen(this->moduleName.c_str(), RTLD_NOW);
}

Extensions::ExtensionLoader::~ExtensionLoader()
{
  //delete(this->klass);
  this->klass = nullptr;
}

void
Extensions::ExtensionLoader::load(Runtime::iStandardClass* obj)
{

  if (!this->handle)
  {
    this->errored = true;
    return;
  }

  this->create  = (createiStandardClassT*)dlsym(handle,"create");
  this->destroy = (destroyiStandardClassT*)dlsym(handle,"destroy");
  if (!this->create || !this->destroy)
  {
    this->errored = true;
    this->errorMsg = std::string(dlerror());
    return;
  }

  // TODO:
  //  this will eventually register a module for the user to see loaded modules
  this->klass = this->create(obj);

}

void
Extensions::ExtensionLoader::destroyExtension()
{
  this->destroy(this->klass);
}


Runtime::iStandardClass*
Extensions::ExtensionLoader::getClass()
{
  return this->klass;
}