#include <iostream>
#include <fstream>
#include "shared/config.hpp"
#include "dev/debugnew/debug_new.h"
#include "shared/ast/tree.hpp"
#include "ext/loader/driverLoader.hpp"
#include "mate/compiler/codeGenerator.hpp"
#include "shared/runtime/langRuntime.hpp"

#include "ext/loader/extensionLoader.hpp"
#include "cli/args.hpp"

#include <vector>

int
main( const int argc, const char **argv )
{

  //
  // FLAGS
  //

  args::ArgumentParser parser("Mate Compiler v0.0.1", "General usage: mate -c filename -o outfile");
  args::HelpFlag help(parser, "help", "Display the help menu", {'h', "help"});

  args::ValueFlag<std::string> compile(parser, "compile", "Compile a mate source file", {'c'});
  args::ValueFlag<std::string> out(parser, "out", "Output file", {'o'});

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

  //
  // Mate Compiler
  //

  if (compile)
  {
    Runtime::LangRuntime::bootstrap();

    Mate::CodeGenerator *cg = nullptr;
    Extensions::DriverLoader* driver = new Extensions::DriverLoader();
    Extensions::ExtensionLoader *extLoader = new Extensions::ExtensionLoader("sqlite");

    try
    {
      extLoader->load(Runtime::LangRuntime::objectClass);

      driver->load();
      if (driver->loaded())
      {
        driver->getDriver()->parse(args::get(compile).c_str());

        cg = new Mate::CodeGenerator(driver->getDriver()->getTree());
        cg->generate(args::get(out));

      }
    }
    catch (Exception::iException &e)
    {
      std::cout << e.what() << std::endl;
    }

    if (cg != nullptr)
    {
      delete(cg);
    }

    Runtime::LangRuntime::destroy();

    delete(extLoader);
    delete(driver);
  }

  return 0;
}
