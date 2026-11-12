#include "pch.h"
#include "FriendsPage.xaml.h"
#include "..\Components\WebViewPage.xaml.h"
#include "..\Arkiv\ArkivSettings.h"

using namespace Arkiv::Views;
using namespace Arkiv::Controls;
using namespace Arkiv;
using namespace Platform;
using namespace Windows::UI::Xaml::Navigation;

FriendsPage::FriendsPage()
{
    InitializeComponent();

    auto settings = Arkiv::ArkivSettings::GetInstance();
    pageImpl->SetSearchType(2);
    pageImpl->SetPageTheme(2);
    SetDefaultUrl(settings->FriendsURL());
}
