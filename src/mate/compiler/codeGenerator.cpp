#include "mate/compiler/codeGenerator.hpp"

Mate::CodeGenerator::~CodeGenerator()
{
  this->tree = nullptr;
}

void
Mate::CodeGenerator::generate()
{
  this->tree->compile( (this) );
  std::cout << "state: " << this->getState() << std::endl;
}

