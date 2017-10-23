#include "shared/pawn/instructions.hpp"

std::string Pawn::Instructions::instructions[] = {
  "NOOP",
  "PUSH_INTEGER",
  "PUSH_STRING",
  "PUSH_ARRAY",
  "SET_LOCAL",
  "PUSH_SELF",
  "CALL",
  "GET_LOCAL",
  "RETURN",
  "POP"
};