#include "pch.h"
#include "GamesPage.xaml.h"
#include "..\Components\WebViewPage.xaml.h"
#include "..\Arkiv\ArkivSettings.h"

using namespace Arkiv::Views;
using namespace Arkiv::Controls;
using namespace Arkiv;
using namespace Platform;

GamesPage::GamesPage()
{
    InitializeComponent();

    auto settings = Arkiv::ArkivSettings::GetInstance();
    pageImpl->SetSearchType(1);
    pageImpl->SetPageTheme(1);
    SetDefaultUrl(settings->GamesURL());
}
