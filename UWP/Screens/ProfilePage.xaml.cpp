#include "pch.h"
#include "ProfilePage.xaml.h"
#include "..\Components\WebViewPage.xaml.h"
#include "..\Arkiv\ArkivSettings.h"

using namespace Arkiv::Views;
using namespace Arkiv::Controls;
using namespace Arkiv;
using namespace Platform;
using namespace Windows::UI::Xaml::Navigation;

ProfilePage::ProfilePage()
{
    InitializeComponent();

    auto settings = Arkiv::ArkivSettings::GetInstance();
    pageImpl->SetPageTheme(3);
    SetDefaultUrl(settings->ProfileURL());
}
