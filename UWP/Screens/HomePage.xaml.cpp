#include "pch.h"
#include "HomePage.xaml.h"
#include "..\Components\WebViewPage.xaml.h"
#include "..\Arkiv\ArkivSettings.h"

using namespace Arkiv::Views;
using namespace Arkiv::Controls;
using namespace Arkiv;
using namespace Platform;
using namespace Windows::UI::Xaml::Navigation;

HomePage::HomePage()
{
    InitializeComponent();

    auto settings = Arkiv::ArkivSettings::GetInstance();
    pageImpl->SetSearchType(2);
    pageImpl->SetPageTheme(1);
    SetDefaultUrl(settings->HomeURL());
}
