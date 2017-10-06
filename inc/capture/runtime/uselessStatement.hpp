#ifndef __USELESSSTATEMENTEXCEPTION
#define __USELESSSTATEMENTEXCEPTION 1

#include "shared/exception/iException.hpp"

namespace Exception
{

  class UselessStatement : public iException
  {

    private:
      std::string filename;
      std::string klass;
      std::string objToString;
      int line;
      int column;

    public:
      UselessStatement(std::string className, std::string objToString, std::string filename, int line, int column)
      {
        this->filename = filename;
        this->line = line;
        this->column = column;
        this->klass = className;
        this->objToString = objToString;
        this->e = USELESS_STATEMENT;
      };

      const char * what () const throw ()
      {
        this->check->load(this->e);
        std::vector<std::string> p;

        p.push_back("USELESS STATEMENT");
        p.push_back(this->klass);
        p.push_back(this->objToString);
        p.push_back(this->filename);
        p.push_back(std::to_string(this->line));
        p.push_back(std::to_string(this->column));

        return this->check->getFactory()->create()->with(p)->emit().c_str();
      };

  };

}

#endif