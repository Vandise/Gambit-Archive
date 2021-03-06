#ifndef __DRIVERMODULE_LOADER_HPP__
#define __DRIVERMODULE_LOADER_HPP__ 1

#include "shared/lang/iDriver.hpp"
#include "ext/loader/iModuleLoader.hpp"

#include "capture/loader/invalidInterface.hpp"
#include "capture/loader/moduleNotFound.hpp"

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
      void load();
      Extensions::iDriver* getDriver();
  };
}

#endif