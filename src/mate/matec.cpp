#include <iostream>
#include <fstream>
#include "shared/config.hpp"
#include "dev/debugnew/debug_new.h"
#include "shared/ast/tree.hpp"
#include "ext/loader/driverLoader.hpp"
#include "mate/compiler/codeGenerator.hpp"
#include "shared/runtime/langRuntime.hpp"

int
main( const int argc, const char **argv )
{

  Extensions::DriverLoader* driver = new Extensions::DriverLoader();
  Runtime::LangRuntime::bootstrap();

  try
  {
    if ( argc == 2 )
    {
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

  delete(driver);

  Runtime::LangRuntime::destroy();

  return 0;
}
