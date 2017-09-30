#ifndef __SQLITE3_GAMBITEXT
#define __SQLITE3_GAMBITEXT 1

#include <iostream>
#include "sqlite/lib/sqlite3.h"
#include "shared/runtime/iStandardClass.hpp"

namespace Runtime
{

  class Sqlite : public Runtime::iStandardClass
  {

    private:
      sqlite3 *db;
      int rc;

    public:

      using Runtime::iStandardClass::iStandardClass;

      virtual ~Sqlite()
      {
        std::cout << "deleting sqlite" << std::endl;
      };

  };

}

#endif