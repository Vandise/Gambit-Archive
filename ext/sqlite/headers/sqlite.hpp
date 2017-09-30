#ifndef __SQLITE3_GAMBITEXT
#define __SQLITE3_GAMBITEXT 1

#include <iostream>
#include "sqlite/lib/sqlite3.h"
#include "shared/runtime/iStandardClass.hpp"
#include "shared/runtime/iMethod.hpp"

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

  //
  //  METHODS
  //

  class SqliteInitializeMethod : public Runtime::iMethod
  {

    public:

      virtual Runtime::iStandardClass* call(Runtime::iStandardClass *receiver, std::vector<Runtime::iStandardClass*> arguments)
      {
        std::cout << "called initialize" << std::endl;
        return receiver;
      };

  };

}

#endif