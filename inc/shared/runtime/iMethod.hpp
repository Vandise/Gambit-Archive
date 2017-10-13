#ifndef __RUNTIMEiMETHOD
#define __RUNTIMEiMETHOD 1

#include <string>
#include <vector>

#define PARAMETER_TYPE(s) this->methodSignature.push_back(s); this->parameterCount++;

namespace Runtime
{

  class iStandardClass;

  class iMethod
  {

    protected:
      int parameterCount = 0;
      std::vector<std::string> methodSignature;

    public:

      virtual Runtime::iStandardClass* call(Runtime::iStandardClass *receiver, std::vector<Runtime::iStandardClass*> arguments) = 0;

      virtual std::string generateMethodName(std::string name)
      {
        std::vector<std::string>::iterator it;
        for (it = this->methodSignature.begin(); it != this->methodSignature.end(); it++)
        {
          name.append("_").append(*it);
        }
        return name;
      };

      virtual int getParameterCount()
      {
        return this->parameterCount;
      };

      virtual ~iMethod(){};

  };

}

#endif