#ifndef __iVMFRAME
#define __iVMFRAME 1

#include <string>
#include <iostream>

namespace VM
{

  class iFrame
  {
    protected:
      std::string frameName;

    public:

      iFrame(std::string frameName)
      {
        this->frameName = frameName;
      };

      virtual ~iFrame(){};

      virtual std::string getFrameName()
      {
        return this->frameName;
      };
  };

}

#endif