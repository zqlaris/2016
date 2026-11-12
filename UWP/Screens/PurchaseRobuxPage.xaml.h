#pragma once

#include "PurchaseRobuxPage.g.h"

namespace Arkiv
{
    ref class ArkivSettings;

    namespace Controls
    {
        ref class WebView;
    }
}

namespace Arkiv
{
    namespace Views
    {
        [Windows::Foundation::Metadata::WebHostHidden]
        public ref class PurchaseRobuxPage sealed
        {
        public:
            PurchaseRobuxPage();

        private:
            void OnCloseButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
        };
    }
}
