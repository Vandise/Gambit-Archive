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
  /*
  Runtime::Sqlite *sqliteExt = dynamic_cast<Runtime::Sqlite*>(obj);
  if (sqliteExt != nullptr)
  {
    std::cout << "valid sqlite class passed in for deletion" << std::endl;
  }
  */
   //delete obj;
}