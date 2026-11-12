#ifndef ARKIVINFO_H
#define ARKIVINFO_H

#include <iostream>

#include "rbx/Debug.h"

class ArkivInfo
{
public:

    static ArkivInfo& getArkivInfo()
    {
        static ArkivInfo arkivInfo;
        return arkivInfo;
    }

    std::string getAssetFolderPath()
    {
        if(assetFolderPath.empty())
            RBXASSERT("Asset Path is not Set");

        return assetFolderPath;
    }

    void setAssetFolderPath(std::string assetPath)
    {
        assetFolderPath = assetPath;
    }

private:
    ArkivInfo() {};
    ArkivInfo(ArkivInfo const&);
    void operator=(ArkivInfo const&);
    std::string assetFolderPath;

};

#endif // ARKIVINFO_H
