#ifndef __iDRIVER_HPP__
#define __iDRIVER_HPP__ 1

namespace AST
{
  class Tree;
}

namespace Extensions
{

  class iDriver
  {

    public:
      virtual int parse( const char *filename ) = 0;
      virtual AST::Tree* getTree() = 0;
      virtual ~iDriver(){};

  };

}

#endif