#ifndef __MODULENOTFOUNDEXCEPTION
#define __MODULENOTFOUNDEXCEPTION 1

#include "shared/exception/iException.hpp"

namespace Exception
{

  class ModuleNotFound : public iException
  {

    private:
      std::string module;

    public:
      ModuleNotFound(std::string msg, std::string module)
      {
        this->message = msg;
        this->module = module;
        this->e = MODULE_NOT_FOUND;
      };

      const char * what () const throw ()
      {
        std::vector<std::string> p;
        p.push_back("MODULE NOT LOADED");
        return Check::MessageFactory(this->e).create()->with(p)->emit().c_str();
      };

  };

}

#endif