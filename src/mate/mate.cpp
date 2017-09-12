#include <iostream>
#include <fstream>
#include "shared/config.hpp"
#include "dev/debugnew/debug_new.h"
#include "ext/loader/driverLoader.hpp"

int
main( const int argc, const char **argv )
{
  if ( argc == 2 )
  {
    Extensions::DriverLoader* driver = new Extensions::DriverLoader();
    driver->load();
    if (driver->loaded())
    {
      driver->getDriver()->parse(argv[1]);
    }
    delete(driver);
  }
  return 1;
}
