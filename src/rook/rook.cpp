#include <iostream>
#include <fstream>
#include <cassert>

#include "shared/config.hpp"
#include "dev/debugnew/debug_new.h"
#include "shared/dev/board.hpp"
#include "shared/exception/iException.hpp"
#include "shared/runtime/langRuntime.hpp"
#include "ext/loader/extensionLoader.hpp"
#include "cli/args.hpp"
#include "rook/scanner.hpp"
#include "rook/parser.tab.hpp"
#include "rook/ast/rookTree.hpp"
#include "rook/vm/pawnExecutor.hpp"


#include <iomanip>
#include <ostream>
#include <string>

struct hexdump {
  void const* data;
  int len;

  hexdump(void const* data, int len) : data(data), len(len) {}

  template<class T>
  hexdump(T const& v) : data(&v), len(sizeof v) {}

  friend
  std::ostream& operator<<(std::ostream& s, hexdump const& v) {
    // don't change formatting for s
    std::ostream out (s.rdbuf());
    out << std::hex << std::setfill('0');

    unsigned char const* pc = reinterpret_cast<unsigned char const*>(v.data);

    std::string buf;
    buf.reserve(17); // premature optimization

    int i;
    for (i = 0; i < v.len; ++i, ++pc) {
      if ((i % 16) == 0) {
        if (i) {
          out << "  " << buf << '\n';
          buf.clear();
        }
        out << "  " << std::setw(4) << i << ' ';
      }

      out << ' ' << std::setw(2) << unsigned(*pc);
      buf += (0x20 <= *pc && *pc <= 0x7e) ? *pc : '.';
    }
    if (i % 16) {
      char const* spaces16x3 = "                                                ";
      out << &spaces16x3[3 * (i % 16)];
    }
    out << "  " << buf << '\n';

    return s;
  }
};

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

    Dev::Board::initialize();

    Dev::Board::sendMessage(std::string("Hello World"));

    Runtime::LangRuntime::bootstrap();
    // eventually this will load all extensions specified in a file
    Extensions::ExtensionLoader *extLoader = new Extensions::ExtensionLoader("sqlite");

    Rook::Scanner *scanner = nullptr;
    Rook::Parser  *parser  = nullptr;
    RookAST::RookTree *tree = nullptr;
    RookVM::PawnExecutor *vm = nullptr;

    try
    {
      extLoader->load(Runtime::LangRuntime::objectClass);

      std::string filename = args::get(run);

      std::ifstream in_file( filename );
      if( ! in_file.good() ) exit( EXIT_FAILURE );

      tree = new RookAST::RookTree();
      vm = new RookVM::PawnExecutor(tree);

      scanner = new Rook::Scanner( &in_file, std::string(filename) );
      parser = new Rook::Parser( (*scanner), (*tree) );

      parser->parse();

      vm->run();

    }
    catch (Exception::iException &e)
    {
      std::cout << e.what() << std::endl;
    }

    Runtime::LangRuntime::destroy();
    delete(extLoader);

    if (scanner != nullptr) delete(scanner);
    if (parser != nullptr) delete(parser);
    if (vm != nullptr) delete(vm);

    Dev::Board::terminate();
  }

  return 0;
}
