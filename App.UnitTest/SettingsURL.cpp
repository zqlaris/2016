#include <boost/test/unit_test.hpp>

#include "ArkivServicesTools.h"

BOOST_AUTO_TEST_SUITE(SettingsUrl)

BOOST_AUTO_TEST_CASE(SettingsUrlProd)
{
	std::string testUrl = "http://clientsettings.api.arkiv.com/Setting/QuietGet/Test/?apiKey=TestKey";
	std::string url = GetSettingsUrl("www.arkiv.com", "Test", "TestKey");
	BOOST_CHECK_EQUAL(url, testUrl);

	url = GetSettingsUrl("http://www.arkiv.com", "Test", "TestKey");
	BOOST_CHECK_EQUAL(url, testUrl);
}

BOOST_AUTO_TEST_CASE(SettingsUrlNewGametest)
{
	std::string testUrl = "http://clientsettings.api.gametest1.arkivlabs.com/Setting/QuietGet/Test/?apiKey=TestKey";
	std::string url = GetSettingsUrl("www.gametest1.arkivlabs.com", "Test", "TestKey");
	BOOST_CHECK_EQUAL(url, testUrl);

	url = GetSettingsUrl("http://www.gametest1.arkivlabs.com", "Test", "TestKey");
	BOOST_CHECK_EQUAL(url, testUrl);
}

BOOST_AUTO_TEST_CASE(SettingsUrlGametest)
{
	std::string testUrl = "http://clientsettings.api.gametest1.arkiv.com/Setting/QuietGet/Test/?apiKey=TestKey";
	std::string url = GetSettingsUrl("www.gametest1.arkiv.com", "Test", "TestKey");
	BOOST_CHECK_EQUAL(url, testUrl);

	url = GetSettingsUrl("http://www.gametest1.arkiv.com", "Test", "TestKey");
	BOOST_CHECK_EQUAL(url, testUrl);
}

BOOST_AUTO_TEST_SUITE_END()
