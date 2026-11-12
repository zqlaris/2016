#include "pch.h"
#include "PurchaseBCPage.xaml.h"
#include "..\Components\WebView.xaml.h"
#include "..\Arkiv\ArkivSettings.h"
#include "..\Arkiv\ResourceStrings.h"

using namespace Arkiv::Views;
using namespace Arkiv::Controls;
using namespace Arkiv;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media::Imaging;

PurchaseBCPage::PurchaseBCPage()
{
    InitializeComponent();

    txtTitle->Text = GetResourceString(L"PurchaseBCTitle");

    if (txtBalance != nullptr)
    {
        txtBalance->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
    }

    btnClose_image->Source =
        ref new BitmapImage(ref new Uri(L"ms-appx:///Assets/Shell/cancelButton.png"));

    btnClose->Click += ref new RoutedEventHandler(this, &PurchaseBCPage::OnCloseButtonClick);

    auto settings = ArkivSettings::GetInstance();
    wvContent->Source = ref new Uri(settings->PurchaseBCURL());
}

void PurchaseBCPage::OnCloseButtonClick(Object^ sender, RoutedEventArgs^ e)
{
    this->Hide();
}
