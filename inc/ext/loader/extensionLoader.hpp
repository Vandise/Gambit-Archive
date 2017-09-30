#ifndef __EXTENSIONMODULE_LOADER_HPP__
#define __EXTENSIONMODULE_LOADER_HPP__ 1

#include "shared/runtime/iStandardClass.hpp"
#include "ext/loader/iModuleLoader.hpp"

typedef Runtime::iStandardClass* createiStandardClassT(Runtime::iStandardClass* obj);
typedef void destroyiStandardClassT(Runtime::iStandardClass*);

namespace Extensions
{

  class ExtensionLoader : public Extensions::iModuleLoader
  {
    private:
      createiStandardClassT* create;
      destroyiStandardClassT* destroy;
      Runtime::iStandardClass* klass;

    public:

      using iModuleLoader::iModuleLoader;
      ExtensionLoader(std::string module);

      virtual ~ExtensionLoader();
      using Extensions::iModuleLoader::load;
      void load(Runtime::iStandardClass* obj);
      Runtime::iStandardClass* getClass();

  };
}

#endif