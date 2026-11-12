#pragma once

#include "V8Tree/Service.h"

namespace RBX {

	extern const char* const sArkivReplicatedStorage;

	class ArkivReplicatedStorage
		: public DescribedCreatable<ArkivReplicatedStorage, Instance, sArkivReplicatedStorage, Reflection::ClassDescriptor::INTERNAL, Security::ArkivScript>
		, public Service
	{
	public:
		ArkivReplicatedStorage();
	};

}
