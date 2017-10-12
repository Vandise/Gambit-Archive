#ifndef __ROOK_VM_LITERALSTABLE
#define __ROOK_VM_LITERALSTABLE 1

#include <string>
#include <vector>

namespace RookVM
{

  class LiteralsTable
  {

    protected:
      std::vector<std::string> literals;

    public:

      LiteralsTable(){};

      virtual ~LiteralsTable(){};

      std::string getLiteral(int offset)
      {
        return this->literals[offset];
      }

      void addLiteral(std::string literal)
      {
        this->literals.push_back(literal);
      };

  };

}

#endif