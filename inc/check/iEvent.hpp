#ifndef __iCHECKEVENT
#define __iCHECKEVENT 1

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

#define PUSH_BUFFER this->buffer + strlen(this->buffer)

#define INITIALIZE_REFERENCES std::vector<std::string> references; this->emitReferenceLine();
#define DEFINE_REFERENCE(ref) references.push_back(ref);
#define EMIT_REFERENCES {                       \
  for(int i = 0; i < references.size(); i++ ) { \
    this->emitReference(references[i], i + 1);  \
  }                                             \
}

using namespace std;

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

      virtual void emitTrace()
      {
        sprintf(PUSH_BUFFER,
          "\n%s -- %s -------------------------------------------- %s \n\n", this->yellow.c_str(), "TRACE", this->reset.c_str());
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
      };

      virtual void emitReference(std::string msg, int refCt)
      {
        sprintf(PUSH_BUFFER,
          "\t\t%d.) %s \n", refCt, msg.c_str());
      };

      virtual void emitStackTrace(std::string filename, std::string errline, std::string column)
      {
        int line_number = std::stoi(errline);
        int column_number = std::stoi(column) - 3;
        int i = 1;
        std::string line;
        std::ifstream error_file(filename);

        this->emitLineLabel(
          std::string(this->cyan).append("In file ")
            .append(filename).append(" on line ").append(errline).append(this->reset.c_str())
        );

        if (error_file)
        {
          while(std::getline(error_file, line))
          {
            if (i >= line_number - 5 || i <= line_number + 5)
            {
              this->emitLine(std::to_string(i).append(": ").append(line));
            }
            if (i == line_number)
            {
              std::string culprit = "";
              culprit.assign(std::to_string(i).length() + 2, ' ');
              culprit.append(this->red);
              int j = 0;
              while(j <= column_number)
              {
                culprit.append("~");
                j++;
              }
              culprit.append("^");
              culprit.append(this->reset.c_str());
              this->emitLine(culprit);
            }
            i++;
          }
        }

      };
  };
}

#endif