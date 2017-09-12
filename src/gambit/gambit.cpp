#include "gambit/lang/driver.hpp"

extern "C" Gambit::Driver* create()
{
    return new Gambit::Driver();
}

extern "C" void destroy(Gambit::Driver* Tl)
{
   delete Tl ;
}