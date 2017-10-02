#include "gambit/lang/driver.hpp"

Gambit::Driver::Driver()
{
  this->tree = new Gambit::Tree();
}

Gambit::Driver::~Driver()
{
   delete(scanner);
   scanner = nullptr;
   delete(parser);
   parser = nullptr;
   delete(this->tree);
   tree = nullptr;
}

int
Gambit::Driver::parse( const char * const filename )
{
   assert( filename != nullptr );
   std::ifstream in_file( filename );
   if( ! in_file.good() ) exit( EXIT_FAILURE );

   delete(scanner);
   try
   {
      scanner = new Gambit::Scanner( &in_file, std::string(filename) );
   }
   catch( std::bad_alloc &ba )
   {
      std::cerr << "Failed to allocate scanner: (" <<
         ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }
   delete(parser);
   try
   {
      parser = new Gambit::Parser( (*scanner), (*this->tree) );
   }
   catch( std::bad_alloc &ba )
   {
      std::cerr << "Failed to allocate parser: (" <<
         ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }

   return parser->parse();;
}

AST::Tree*
Gambit::Driver::getTree()
{
  return this->tree;
}
