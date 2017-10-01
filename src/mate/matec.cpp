#include <iostream>
#include <fstream>
#include "shared/config.hpp"
#include "dev/debugnew/debug_new.h"
#include "shared/ast/tree.hpp"
#include "ext/loader/driverLoader.hpp"
#include "mate/compiler/codeGenerator.hpp"
#include "shared/runtime/langRuntime.hpp"

#include "ext/loader/extensionLoader.hpp"

#include <vector>

int
main( const int argc, const char **argv )
{

  Runtime::LangRuntime::bootstrap();

  Mate::CodeGenerator *cg = nullptr;
  Extensions::DriverLoader* driver = new Extensions::DriverLoader();
  Extensions::ExtensionLoader *extLoader = new Extensions::ExtensionLoader("sqlite");

  try
  {
    if ( argc == 2 )
    {

      extLoader->load(Runtime::LangRuntime::objectClass);

      driver->load();
      if (driver->loaded())
      {
        driver->getDriver()->parse(argv[1]);

        cg = new Mate::CodeGenerator(driver->getDriver()->getTree());
        cg->generate();

      }
    }

  }
  catch (Exception::iException &e)
  {
    std::cout << e.what() << std::endl;
  }

  if (cg != nullptr)
  {
    delete(cg);
  }

  Runtime::LangRuntime::destroy();

  delete(extLoader);
  delete(driver);

  return 0;
}
