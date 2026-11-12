#include "pch.h"
#include "ArkivSettings.h"

using namespace Arkiv;
using namespace Platform;

ArkivSettings^ ArkivSettings::s_instance = nullptr;

ArkivSettings::ArkivSettings()
    : m_baseDomain(L"www.freblx.com")
    , m_baseURL(L"http://www.freblx.com")
    , m_baseURLWWW(L"http://www.freblx.com")
    , m_baseSecureURL(L"https://www.freblx.com")
    , m_baseApiURL(L"https://api.freblx.com")
    , m_deviceAppVersion(L"1.1.57.0")
    , m_apiUserAgent(L"ArkivUWP/1.1.57.0 (Windows 10)")
    , m_deviceIsTablet(true)
    , m_useLegacyUrls(true)
{
}

ArkivSettings::~ArkivSettings()
{
}

ArkivSettings^ ArkivSettings::GetInstance()
{
    if (s_instance == nullptr)
    {
        s_instance = ref new ArkivSettings();
    }
    return s_instance;
}

bool ArkivSettings::DeviceIsTablet()
{
    return m_deviceIsTablet;
}

String^ ArkivSettings::DeviceAppVersion()
{
    return m_deviceAppVersion;
}

void ArkivSettings::SetDomain(String^ newDomain)
{
    if (newDomain != nullptr)
    {
        m_baseDomain = newDomain;
        m_baseURL = L"http://" + newDomain;
        m_baseURLWWW = L"http://" + newDomain;
        m_baseSecureURL = L"https://" + newDomain;
        m_baseApiURL = L"https://api." + newDomain;
    }
}

String^ ArkivSettings::GetBaseURL()
{
    return m_baseURL;
}

String^ ArkivSettings::GetBaseURLWWW()
{
    return m_baseURLWWW;
}

String^ ArkivSettings::GetBaseSecureURL()
{
    return m_baseSecureURL;
}

String^ ArkivSettings::GetBaseApiURL()
{
    return m_baseApiURL;
}

String^ ArkivSettings::HomeURL()
{
    return m_baseSecureURL + L"/";
}

String^ ArkivSettings::GamesURL()
{
    return m_baseSecureURL + L"/games";
}

String^ ArkivSettings::CatalogURL()
{
    return m_baseSecureURL + L"/catalog/";
}

String^ ArkivSettings::CharacterURL()
{
    return m_baseSecureURL + L"/My/Character.aspx";
}

String^ ArkivSettings::InventoryURL()
{
    return m_baseSecureURL + (m_useLegacyUrls ? L"/My/Stuff.aspx" : L"/inventory");
}

String^ ArkivSettings::TradeURL()
{
    return m_baseSecureURL + L"/My/Money.aspx";
}

String^ ArkivSettings::ForumUrl()
{
    return m_baseSecureURL + L"/Forum/default.aspx";
}

String^ ArkivSettings::HelpURL()
{
    return L"https://en.help.freblx.com/hc/en-us";
}

String^ ArkivSettings::SettingsURL()
{
    return m_baseSecureURL + L"/my/account";
}

String^ ArkivSettings::ProfileURL()
{
    return m_baseSecureURL + (m_useLegacyUrls ? L"/User.aspx" : L"/users/profile");
}

String^ ArkivSettings::MessagesURL()
{
    return m_baseSecureURL + (m_useLegacyUrls ? L"/my/messages/#!/inbox" : L"/inbox");
}

String^ ArkivSettings::GroupsURL()
{
    return m_baseSecureURL + (m_useLegacyUrls ? L"/My/Groups.aspx" : L"/my-groups");
}

String^ ArkivSettings::LeaderboardsURL()
{
    return m_baseSecureURL + L"/leaderboards";
}

String^ ArkivSettings::FriendsURL()
{
    return m_baseSecureURL + (m_useLegacyUrls ? L"/friends.aspx" : L"/friends");
}

String^ ArkivSettings::SearchUsersURL(String^ term)
{
    return m_baseURL + L"/users/search?keyword=" + term;
}

String^ ArkivSettings::SearchGamesURL(String^ q)
{
    return m_baseURL + L"/games/?Keyword=" + q;
}

String^ ArkivSettings::LoginURL(String^ username, String^ password)
{
    return m_baseApiURL + L"/login/v1?username=" + username + L"&password=" + password;
}

String^ ArkivSettings::SignupURL()
{
    return m_baseSecureURL + L"/signup";
}

String^ ArkivSettings::SignupV1URL()
{
    return m_baseApiURL + L"/signup/v1";
}

String^ ArkivSettings::UsernameValidationURL(String^ username)
{
    return m_baseApiURL + L"/signup/is-username-valid?username=" + username;
}

String^ ArkivSettings::PasswordValidationURL(String^ username, String^ password)
{
    return m_baseApiURL + L"/signup/is-password-valid?username=" + username + L"&password=" + password;
}

String^ ArkivSettings::UsernameSuggestionURL(String^ username)
{
    return m_baseApiURL + L"/UserCheck/getrecommendedusername?usernameToTry=" + username;
}

String^ ArkivSettings::LogoutURL()
{
    return m_baseApiURL + L"/logout";
}

String^ ArkivSettings::CaptchaURL()
{
    return m_baseApiURL + L"/mobile-captcha";
}

String^ ArkivSettings::CaptchaSolvedURL()
{
    return m_baseApiURL + L"/mobile-captcha-solved";
}

String^ ArkivSettings::LoginCaptchaValidateURL()
{
    return m_baseApiURL + L"/captcha/validate/login";
}

String^ ArkivSettings::SignupCaptchaValidateURL()
{
    return m_baseApiURL + L"/captcha/validate/signup";
}

String^ ArkivSettings::InitializeDeviceURL()
{
    return m_baseApiURL + L"/device/initialize";
}

String^ ArkivSettings::AccountInfoApiURL()
{
    return m_baseApiURL + L"/users/account-info";
}

String^ ArkivSettings::BalanceApiURL()
{
    return m_baseApiURL + L"/my/balance";
}

String^ ArkivSettings::BlogURL()
{
    return L"http://blog.arkiv.com/";
}

String^ ArkivSettings::UpgradeCheckURL()
{
    return m_baseApiURL + L"/mobileapi/check-app-version?appVersion=AppUWPV1.1.57";
}

String^ ArkivSettings::AppStoreLaunchURL()
{
    return L"ms-windows-store://pdp?productid=9NBLGGG5M842";
}

String^ ArkivSettings::AppStoreListingURL()
{
    return L"https://www.microsoft.com/store/apps/9NBLGGG5M842";
}

String^ ArkivSettings::AppStoreUpdatesURL()
{
    return L"ms-windows-store://review/?productid=9NBLGGG5M842";
}

String^ ArkivSettings::PurchaseRobuxURL()
{
    return m_baseSecureURL + L"/upgrades/robux";
}

String^ ArkivSettings::PurchaseRobuxV2URL()
{
    return m_baseApiURL + L"/purchase/robux";
}

String^ ArkivSettings::PurchaseBCURL()
{
    return L"ms-windows-store://downloadsandupdates";
}

String^ ArkivSettings::StoreValidatePurchaseURL(String^ productID)
{
    return m_baseApiURL + L"/windows/v1/validate-purchase?productId=" + productID;
}

String^ ArkivSettings::StoreReportPurchaseURL(String^ transactionID)
{
    return m_baseApiURL + L"/windows/v1/report-purchase?transactionIds[0]=" + transactionID;
}

String^ ArkivSettings::AnalyticsEphemeralURL(String^ apiKey, String^ counterName, String^ amount)
{
    return L"https://ephemeralcountersoapi.freblx.com/v1.1/Counters/Increment/?apiKey=" + apiKey + L"&counterName=" + counterName + L"&amount=" + amount;
}

String^ ArkivSettings::AnalyticsInfluxV2URL(String^ serverURL, String^ database, String^ user, String^ password, String^ timePrecisionID)
{
    return serverURL + L"/influx/v2?db=" + database + L"&u=" + user + L"&p=" + password + L"&precision=" + timePrecisionID;
}

String^ ArkivSettings::ApiUserAgent()
{
    return m_apiUserAgent;
}
