#ifndef __DRIVERMODULE_LOADER_HPP__
#define __DRIVERMODULE_LOADER_HPP__ 1

#include "shared/lang/iDriver.hpp"
#include "ext/loader/iModuleLoader.hpp"

typedef Extensions::iDriver* createDriverT();
typedef void destroyDriverT(Extensions::iDriver*);

namespace Extensions
{

  class DriverLoader : public Extensions::iModuleLoader
  {
    private:
      Extensions::iDriver* driver;
      createDriverT* create;
      destroyDriverT* destroy;

    public:

      using iModuleLoader::iModuleLoader;

      DriverLoader();
      virtual ~DriverLoader();
      bool load();
      Extensions::iDriver* getDriver();
  };
}

#endif