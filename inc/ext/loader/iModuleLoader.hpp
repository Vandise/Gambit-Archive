#ifndef __iMODULE_LOADER_HPP__
#define __iMODULE_LOADER_HPP__ 1

#include <dlfcn.h>
#include <string>
#include <iostream>

namespace Extensions
{

  class iModuleLoader
  {

    protected:

      std::string moduleName;
      std::string errorMsg;
      bool errored = false;
      void* handle;

    public:

      iModuleLoader()=default;

      iModuleLoader(std::string moduleName)
      {
        this->moduleName = moduleName;
        this->handle = dlopen(this->moduleName.c_str(), RTLD_NOW);
        if (!this->handle)
        {
          this->errored = true;
          this->errorMsg = std::string(dlerror());
        }
      };

      virtual ~iModuleLoader()
      {
        dlclose(this->handle);
      };

      virtual bool load()
      {
        return false;
      };

      bool loaded()
      {
        return !this->errored;
      };

      std::string getError()
      {
        return this->errorMsg;
      };

  };
}

#endif