#include "shared/pawn/instructions.hpp"

std::string Pawn::Instructions::instructions[] = {
  "NOOP",
  "PUSH_INTEGER",
  "PUSH_STRING",
  "PUSH_ARRAY",
  "SET_LOCAL",
  "POP"
};