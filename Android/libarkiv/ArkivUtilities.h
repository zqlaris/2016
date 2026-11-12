#ifndef ARKIVUTILITIES_H
#define ARKIVUTILITIES_H

#include "rbx/rbxTime.h"

class ArkivUtilities
{

public:

    static ArkivUtilities& getArkivUtilities()
    {

        static ArkivUtilities arkivUtilities;
        return arkivUtilities;
    }

    RBX::Timer<RBX::Time::Fast>& getGameTimer() { return gameTimer; };


private:
    ArkivUtilities() {};
    ArkivUtilities(ArkivUtilities const&);
    void operator=(ArkivUtilities const&);

    RBX::Timer<RBX::Time::Fast> gameTimer;
};



#endif // ARKIVUTILITIES_H
