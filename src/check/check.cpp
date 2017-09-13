#include "check/messageFactory.hpp"

extern "C" Check::MessageFactory* create(CaptureEvents evt)
{
    return new Check::MessageFactory(evt);
}

extern "C" void destroy(Check::MessageFactory* Tl)
{
   delete Tl ;
}