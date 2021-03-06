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
        this->check->load(this->e);
        std::vector<std::string> p;
        p.push_back("MODULE NOT LOADED");
        p.push_back(
          std::string("Unable to load module: ").append(this->module)
        );
        p.push_back(std::string("The module ").append(this->module).append(" exists in the lib directory."));
        return this->check->getFactory()->create()->with(p)->emit().c_str();
      };

  };

}

#endif