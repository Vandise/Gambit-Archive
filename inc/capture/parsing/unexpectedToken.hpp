#ifndef __UNEXPECTEDTOKENEXCEPTION
#define __UNEXPECTEDTOKENEXCEPTION 1

#include "shared/exception/iException.hpp"

namespace Exception
{

  class UnexpectedToken : public iException
  {

    private:
      std::string error;
      std::string filename;
      int line;
      int column;

    public:

      UnexpectedToken(std::string error, std::string filename, int line, int column)
      {
        this->filename = filename;
        this->line = line;
        this->column = column;
        this->error = error;
        this->e = INVALID_TOKEN;
      };

      const char * what () const throw ()
      {
        this->check->load(this->e);
        std::vector<std::string> p;

        p.push_back("INVALID TOKEN");
        p.push_back(this->error);
        p.push_back(this->filename);
        p.push_back(std::to_string(this->line));
        p.push_back(std::to_string(this->column));

        return this->check->getFactory()->create()->with(p)->emit().c_str();
      };

  };

}

#endif