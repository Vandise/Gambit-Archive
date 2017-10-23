#ifndef __OPCODE_INSTRUCTIONS
#define __OPCODE_INSTRUCTIONS 1

#include <string>

namespace Pawn
{

  class Instructions
  {

    private:

      static std::string instructions[];

    public:

      typedef enum {
        NOOP,
        PUSH_INTEGER,
        PUSH_STRING,
        PUSH_ARRAY,
        SET_LOCAL,
        PUSH_SELF,
        CALL,
        GET_LOCAL,
        RETURN,
        POP
      } OPCODE;

      static std::string getInstruction(Pawn::Instructions::OPCODE o)
      {
        return Pawn::Instructions::instructions[o];
      };

  };

}

#endif