#include <iostream>
#include <fstream>
#include "shared/config.hpp"
#include "dev/debugnew/debug_new.h"
#include "shared/ast/tree.hpp"
#include "ext/loader/driverLoader.hpp"

int
main( const int argc, const char **argv )
{

  Extensions::DriverLoader* driver = new Extensions::DriverLoader();

  try
  {
    if ( argc == 2 )
    {
      driver->load();
      if (driver->loaded())
      {
        driver->getDriver()->parse(argv[1]);
        driver->getDriver()->getTree()->compile();
      }
    }

  }
  catch (Exception::iException &e)
  {
    std::cout << e.what() << std::endl;
  }

  delete(driver);

  return 0;
}
