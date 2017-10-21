#ifndef __UNDEFINEDMETHODEXCEPTION
#define __UNDEFINEDMETHODEXCEPTION 1

#include "shared/exception/iException.hpp"

//
//  TODO:
//    Pass in runtime and labels to give method name suggestions
//

namespace Exception
{

  class UndefinedMethodException : public iException
  {

    private:
      std::string filename;
      std::string identifier;
      int line;
      int column;

    public:

      UndefinedMethodException(std::string identifier, std::string filename, int line, int column)
      {
        this->filename = filename;
        this->line = line;
        this->column = column;
        this->identifier = identifier;
        this->e = UNDEFINED_METHOD;
      };

      const char * what () const throw ()
      {
        this->check->load(this->e);
        std::vector<std::string> p;

        p.push_back("UNDEFINED METHOD");
        p.push_back(this->identifier);
        p.push_back(this->filename);
        p.push_back(std::to_string(this->line));
        p.push_back(std::to_string(this->column));

        return this->check->getFactory()->create()->with(p)->emit().c_str();
      };

  };

}

#endif