#include "ext/loader/checkLoader.hpp"

Extensions::CheckLoader::CheckLoader()
{
  this->moduleName = "./lib/check.so";
  this->handle = dlopen(this->moduleName.c_str(), RTLD_NOW);
}

Extensions::CheckLoader::~CheckLoader()
{
  if (this->destroy && this->factory)
  {
    this->destroy(this->factory);
    this->factory = nullptr;
  }
}

bool
Extensions::CheckLoader::load(CaptureEvents evt)
{

  if (!this->handle)
  {
    return false;
  }

  this->create  = (createCheckT*)dlsym(handle,"create");
  this->destroy = (destroyCheckT*)dlsym(handle,"destroy");
  if (!this->create || !this->destroy)
  {
    this->errored = true;
    this->errorMsg = std::string(dlerror());
    return false;
  }
  this->factory = this->create(evt);
  return true;
}

Check::iMessageFactory*
Extensions::CheckLoader::getFactory()
{
  return this->factory;
}