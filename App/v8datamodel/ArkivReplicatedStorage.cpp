#include "stdafx.h"

#include "v8datamodel/ArkivReplicatedStorage.h"

using namespace RBX;

const char* const RBX::sArkivReplicatedStorage = "ArkivReplicatedStorage";

ArkivReplicatedStorage::ArkivReplicatedStorage(void)
{
	setName(sArkivReplicatedStorage);
	setArkivLocked(true);
}
