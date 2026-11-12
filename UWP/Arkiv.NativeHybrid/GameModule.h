#pragma once

#include "Module.h"

namespace Arkiv
{
    namespace NativeHybrid
    {
        [Windows::Foundation::Metadata::WebHostHidden]
        public ref class GameModule sealed : Module
        {
        public:
            GameModule();

        private:
            void LaunchGame(Command^ command);
        };
    }
}
