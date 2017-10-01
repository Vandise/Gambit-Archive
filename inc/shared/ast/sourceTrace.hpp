#ifndef __AST_SOURCETRACE
#define __AST_SOURCETRACE 1

#include <iostream>
#include <string>

namespace AST
{

  class SourceTrace
  {
    public:
      std::string filename;
      int line;
      int column;

      SourceTrace(std::string filename, int line, int column)
      {
        this->filename = filename;
        this->line = line;
        this->column = column;
      };

      virtual ~SourceTrace(){};

  };

}

#endif