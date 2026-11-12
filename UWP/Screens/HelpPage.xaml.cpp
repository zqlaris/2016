#include "pch.h"
#include "HelpPage.xaml.h"
#include "..\Components\WebViewPage.xaml.h"
#include "..\Arkiv\ArkivSettings.h"

using namespace Arkiv::Views;
using namespace Arkiv::Controls;
using namespace Arkiv;
using namespace Platform;
using namespace Windows::UI::Xaml::Navigation;

HelpPage::HelpPage()
{
    InitializeComponent();

    auto settings = Arkiv::ArkivSettings::GetInstance();
    SetDefaultUrl(settings->HelpURL());
}
