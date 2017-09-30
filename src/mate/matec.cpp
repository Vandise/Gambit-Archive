#include <iostream>
#include <fstream>
#include "shared/config.hpp"
#include "dev/debugnew/debug_new.h"
#include "shared/ast/tree.hpp"
#include "ext/loader/driverLoader.hpp"
#include "mate/compiler/codeGenerator.hpp"
#include "shared/runtime/langRuntime.hpp"

#include "ext/loader/extensionLoader.hpp"

int
main( const int argc, const char **argv )
{

  Runtime::LangRuntime::bootstrap();

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

        Mate::CodeGenerator *cg = new Mate::CodeGenerator(driver->getDriver()->getTree());
        cg->generate();

        delete(cg);
      }
    }

  }
  catch (Exception::iException &e)
  {
    std::cout << e.what() << std::endl;
  }

  Runtime::LangRuntime::destroy();

  delete(extLoader);
  delete(driver);

  return 0;
}
