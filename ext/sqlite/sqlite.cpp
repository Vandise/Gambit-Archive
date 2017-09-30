#include "sqlite/headers/sqlite.hpp"

extern "C" Runtime::iStandardClass* create(Runtime::iStandardClass* obj)
{
  Runtime::Sqlite *sqliteExt = new Runtime::Sqlite("Sqlite");

  sqliteExt->setSuperClass(obj);
  obj->setConstant("Sqlite", sqliteExt);

  return sqliteExt;
}

extern "C" void destroy(Runtime::iStandardClass* obj)
{
   delete obj;
}