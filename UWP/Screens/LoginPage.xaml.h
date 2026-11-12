#pragma once

#include "LoginPage.g.h"
#include "..\Arkiv\CloseLandingPageShowAppShell.h"
#include "..\Services\LoginService.h"

namespace Arkiv
{
    namespace Views
    {
        [Windows::Foundation::Metadata::WebHostHidden]
        public ref class LoginPage sealed
        {
        public:
            LoginPage();

            property Arkiv::CloseLandingPageShowAppShell^ closeLandingPageHandler;

        private:
            void OnLoginSucceeded();
            void OnLoginFailed(Arkiv::Services::LoginFailureReason errorCode, int httpStatus);

            void OnLoginButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
            void OnCancelButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
            void OnSignupButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

            Arkiv::Services::LoginService^ m_loginService;
            bool m_closeHandled;
        };
    }
}
