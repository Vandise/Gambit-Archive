#ifndef __AST_NODE
#define __AST_NODE 1

#include <iostream>

namespace AST
{

  class Node
  {
    public:
      virtual ~Node(){};
      virtual void compile() = 0;

  };

}

#endif