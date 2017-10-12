#include <iostream>
#include <fstream>
#include <cassert>

#include "shared/config.hpp"
#include "dev/debugnew/debug_new.h"
#include "shared/exception/iException.hpp"
#include "shared/runtime/langRuntime.hpp"
#include "ext/loader/extensionLoader.hpp"
#include "cli/args.hpp"
#include "rook/scanner.hpp"
#include "rook/parser.tab.hpp"
#include "rook/ast/rookTree.hpp"

int
main( const int argc, const char **argv )
{
  //
  // FLAGS
  //

  args::ArgumentParser parser("Rook VM v0.0.1", "General usage: rook -r filename");
  args::HelpFlag help(parser, "help", "Display the help menu", {'h', "help"});

  args::ValueFlag<std::string> run(parser, "execute", "Run a pawn source file", {'r'});

  try
  {
    parser.ParseCLI(argc, argv);
  }
  catch (args::Help)
  {
    std::cout << parser;
    return 0;
  }
  catch (args::ParseError e)
  {
    std::cerr << e.what() << std::endl;
    std::cerr << parser;
    return 1;
  }
  catch (args::ValidationError e)
  {
    std::cerr << e.what() << std::endl;
    std::cerr << parser;
    return 1;
  }

  if (run)
  {

    Runtime::LangRuntime::bootstrap();
    // eventually this will load all extensions specified in a file
    Extensions::ExtensionLoader *extLoader = new Extensions::ExtensionLoader("sqlite");

    Rook::Scanner *scanner = nullptr;
    Rook::Parser  *parser  = nullptr;
    RookAST::RookTree *tree = nullptr;

    try
    {
      extLoader->load(Runtime::LangRuntime::objectClass);

      std::string filename = args::get(run);

      std::ifstream in_file( filename );
      if( ! in_file.good() ) exit( EXIT_FAILURE );

      tree = new RookAST::RookTree();

      scanner = new Rook::Scanner( &in_file, std::string(filename) );
      parser = new Rook::Parser( (*scanner), (*tree) );

      parser->parse();

      tree->compile();

    }
    catch (Exception::iException &e)
    {
      std::cout << e.what() << std::endl;
    }

    Runtime::LangRuntime::destroy();
    delete(extLoader);
    if (scanner != nullptr) delete(scanner);
    if (parser != nullptr) delete(parser);
    if (tree != nullptr) delete(tree);

  }

  return 0;
}
