#ifndef __iCHECKEVENT
#define __iCHECKEVENT 1

#include <iostream>
#include <string>
#include <vector>

#define PUSH_BUFFER this->buffer + strlen(this->buffer)

#define INITIALIZE_REFERENCES std::vector<std::string> references; this->emitReferenceLine();
#define DEFINE_REFERENCE(ref) references.push_back(ref);
#define EMIT_REFERENCES {                       \
  for(int i = 0; i < references.size(); i++ ) { \
    this->emitReference(references[i], i + 1);  \
  }                                             \
}


namespace Check
{
  class iEvent
  {

    protected:
      char buffer[2048];
      std::string cyan = "\033[36m";
      std::string reset = "\033[0m";
      std::string red = "\033[31m";
      std::string yellow = "\033[33m";
      std::string green = "\033[32m";

    public:

      iEvent() = default;

      virtual Check::iEvent* with(std::vector<std::string> parameters) = 0;
      virtual ~iEvent() = default;

      virtual std::string emit()
      {
        buffer[strlen(buffer)] = '\0';
        return std::string(this->buffer);
      };

      virtual void emitHeader(std::string msg)
      {
        sprintf(PUSH_BUFFER,
          "\n%s -- %s -------------------------------------------- %s \n\n", this->cyan.c_str(), msg.c_str(), this->reset.c_str());
      };

      virtual void emitError(std::string err)
      {
        sprintf(PUSH_BUFFER,
          "\t%s Error: %s \n\n", this->red.c_str(), this->reset.c_str());
        sprintf(PUSH_BUFFER,
          "\t\t%s \n\n", err.c_str());
      };

      virtual void emitLineLabel(std::string msg)
      {
        sprintf(PUSH_BUFFER,
          "\t%s: \n", msg.c_str());
      };

      virtual void emitLine(std::string msg)
      {
        sprintf(PUSH_BUFFER,
          "\t\t%s \n", msg.c_str());
      };

      virtual void emitReferenceLine()
      {
        sprintf(PUSH_BUFFER,
          "\t%s Ensure the following: %s\n\n", this->yellow.c_str(), this->reset.c_str());
      }

      virtual void emitReference(std::string msg, int refCt)
      {
        sprintf(PUSH_BUFFER,
          "\t\t%d.) %s \n", refCt, msg.c_str());
      }
  };
}

#endif