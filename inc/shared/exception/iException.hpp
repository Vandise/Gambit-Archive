#ifndef __iEXCEPTION
#define __iEXCEPTION 1

#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include "shared/exception/captureEvents.hpp"
#include "ext/loader/checkLoader.hpp"

namespace Exception
{

  class iException : public std::exception
  {

    protected:
      std::string message;
      CaptureEvents e = DEFAULT;
      Extensions::CheckLoader* check = new Extensions::CheckLoader();

    public:

      iException() = default;

      iException(std::string message)
      {
        this->message = message;
      };

      virtual ~iException()
      {
        delete(this->check);
      };

      virtual const char * what () const throw ()
      {
        return this->message.c_str();
      };

  };
}

#endif