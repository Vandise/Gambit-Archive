#ifndef __INVAIDINTERFACEEXCEPTION
#define __INVAIDINTERFACEEXCEPTION 1

#include "shared/exception/iException.hpp"

namespace Exception
{

  class InvalidInterface : public iException
  {

    private:
      std::string err;
      std::string expects;
      std::string iName;

    public:
      InvalidInterface(std::string expects, std::string iName, std::string err)
      {
        this->err = err;
        this->expects = expects;
        this->iName = iName;
        this->message = iName.append(" expects ").append(expects).append(" to be defined.");
        this->e = INVALID_INTEFACE;
      };

      const char * what () const throw ()
      {
        this->check->load(this->e);
        std::vector<std::string> p;

        p.push_back("INVALID INTERFACE");
        p.push_back(this->message);
        p.push_back(this->expects);
        p.push_back(this->iName);

        return this->check->getFactory()->create()->with(p)->emit().c_str();
      };

  };

}

#endif