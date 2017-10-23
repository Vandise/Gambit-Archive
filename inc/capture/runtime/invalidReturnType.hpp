#ifndef __DATATYPEMISMATCHRETURN
#define __DATATYPEMISMATCHRETURN 1

#include "shared/exception/iException.hpp"

namespace Exception
{

  class InvalidReturnType : public iException
  {

    private:
      std::string filename;
      std::string identifier;
      std::string expected;
      std::string actual;
      int line;
      int column;

    public:

      InvalidReturnType(std::string identifier, std::string expected, std::string actual, std::string filename, int line, int column)
      {
        this->filename = filename;
        this->expected = expected;
        this->actual = actual;
        this->line = line;
        this->column = column;
        this->identifier = identifier;
        this->e = INVALID_RETURN_TYPE;
      };

      const char * what () const throw ()
      {
        this->check->load(this->e);
        std::vector<std::string> p;

        p.push_back("INVALID RETURN TYPE");
        p.push_back(this->identifier);
        p.push_back(this->expected);
        p.push_back(this->actual);
        p.push_back(this->filename);
        p.push_back(std::to_string(this->line));
        p.push_back(std::to_string(this->column));

        return this->check->getFactory()->create()->with(p)->emit().c_str();
      };

  };

}

#endif