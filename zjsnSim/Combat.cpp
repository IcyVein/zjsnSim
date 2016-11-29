#include "Combat.h"
#include "Defines.h"

Combat::Combat()
{
}

Combat::Combat(Fleet* _myFleet, Fleet* _opFleet, bool _PVEProtect)
{
    myFleet = _myFleet;
    opFleet = _opFleet;
    PVEProtect = _PVEProtect;
}

Combat::~Combat()
{
}
