#ifndef __ASSIGNDATATYPEMISMATCHEXCEPTION
#define __ASSIGNDATATYPEMISMATCHEXCEPTION 1

#include "shared/exception/iException.hpp"

namespace Exception
{

  class AssignDataTypeMismatch : public iException
  {

    private:
      std::string varName;
      std::string d1;
      std::string d2;
      std::string filename;
      int line;
      int column;

    public:
      AssignDataTypeMismatch(std::string varName, std::string d1, std::string d2, std::string filename, int line, int column)
      {
        this->varName = varName;
        this->d1 = d1;
        this->d2 = d2;
        this->filename = filename;
        this->line = line;
        this->column = column;
        this->e = ASSIGN_DATATYPE_MISMATCH;
      };

      const char * what () const throw ()
      {
        this->check->load(this->e);
        std::vector<std::string> p;

        p.push_back("ASSIGNMENT DATATYPE MISMATCH");
        p.push_back(this->varName);
        p.push_back(this->d1);
        p.push_back(this->d2);
        p.push_back(this->filename);
        p.push_back(std::to_string(this->line));
        p.push_back(std::to_string(this->column));

        return this->check->getFactory()->create()->with(p)->emit().c_str();
      };

  };

}

#endif