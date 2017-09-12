#ifndef __iDRIVER_HPP__
#define __iDRIVER_HPP__ 1

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