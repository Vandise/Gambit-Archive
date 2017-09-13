#include "ext/loader/driverLoader.hpp"

Extensions::DriverLoader::DriverLoader()
{
  this->moduleName = "./lib/gambit.so";
  this->handle = dlopen(this->moduleName.c_str(), RTLD_NOW);
}

Extensions::DriverLoader::~DriverLoader()
{
  if (this->destroy && this->driver)
  {
    this->destroy(this->driver);
    this->driver = nullptr;
  }
}

bool
Extensions::DriverLoader::load()
{

  if (!this->handle)
  {
    throw Exception::ModuleNotFound(this->errorMsg, this->moduleName);
  }

  this->create  = (createDriverT*)dlsym(handle,"create");
  this->destroy = (destroyDriverT*)dlsym(handle,"destroy");
  if (!this->create || !this->destroy)
  {
    this->errored = true;
    this->errorMsg = std::string(dlerror());
    return false;
  }
  this->driver = this->create();
  return true;
}

Extensions::iDriver*
Extensions::DriverLoader::getDriver()
{
  return this->driver;
}