#pragma once

namespace Arkiv
{
    namespace NativeHybrid
    {
        ref class Command;

        public delegate void ModuleFunction(Command^ command);
    }
}
