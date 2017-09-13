#ifndef __iEXCEPTION
#define __iEXCEPTION 1

#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include "check/messageFactory.hpp"
#include "shared/exception/captureEvents.hpp"

namespace Exception
{

  class iException : public std::exception
  {

    protected:
      std::string message;
      CaptureEvents e = DEFAULT;

    public:

      iException() = default;

      iException(std::string message)
      {
        this->message = message;
      };

      virtual const char * what () const throw ()
      {
        return this->message.c_str();
      };

  };
}

#endif