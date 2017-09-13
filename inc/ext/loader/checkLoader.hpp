#ifndef __CHECKMODULE_LOADER_HPP__
#define __CHECKMODULE_LOADER_HPP__ 1

#include "shared/check/iMessageFactory.hpp"
#include "ext/loader/iModuleLoader.hpp"

typedef Check::iMessageFactory* createCheckT(CaptureEvents e);
typedef void destroyCheckT(Check::iMessageFactory*);

namespace Extensions
{

  class CheckLoader : public Extensions::iModuleLoader
  {
    private:
      Check::iMessageFactory* factory;
      createCheckT* create;
      destroyCheckT* destroy;

    public:

      using iModuleLoader::iModuleLoader;

      CheckLoader();
      virtual ~CheckLoader();
      using Extensions::iModuleLoader::load;
      bool load(CaptureEvents evt);
      Check::iMessageFactory* getFactory();
  };
}

#endif