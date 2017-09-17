#ifndef __iDRIVER_HPP__
#define __iDRIVER_HPP__ 1

#include "shared/ast/tree.hpp"

namespace Extensions
{

  class iDriver
  {

    public:
      virtual int parse( const char *filename ) = 0;
      virtual ~iDriver(){};

  };

}

#endif