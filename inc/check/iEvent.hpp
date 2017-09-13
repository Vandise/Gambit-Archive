#ifndef __iCHECKEVENT
#define __iCHECKEVENT 1

#include <iostream>
#include <string>
#include <vector>

namespace Check
{
  class iEvent
  {

    protected:
      char buffer[1024];
      std::string cyan = "\033[36m";
      std::string reset = "\033[0m";
      std::string red = "\033[31m";
      std::string yellow = "\033[33m";
      std::string green = "\033[32m";

    public:

      iEvent() = default;

      virtual Check::iEvent* with(std::vector<std::string> parameters) = 0;
      virtual ~iEvent() = default;

      virtual std::string emit()
      {
        return std::string(this->buffer);
      };

      virtual void emitHeader(std::string msg)
      {
        sprintf(this->buffer,
          "%s -- %s -------------------------------------------- %s \n", this->cyan.c_str(), msg.c_str(), this->reset.c_str());
      };
  };
}

#endif