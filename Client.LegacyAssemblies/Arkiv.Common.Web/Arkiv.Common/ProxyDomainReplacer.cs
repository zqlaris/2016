using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Arkiv.Common.Properties;
using Arkiv.Configuration;

namespace Arkiv.Common
{
	public class ProxyDomainReplacer
	{
		private static IEnumerable<string> WhitelistedProxyDomains;

		private static bool EnableProxyUrlDetection
		{
			get
			{
				return Settings.Default.EnableProxyUrlDetection;
			}
		}

		static ProxyDomainReplacer()
		{
			Settings.Default.ReadValueAndMonitorChanges((Settings s) => s.ProxyUrlDomainsCsv, delegate(string newCsv)
			{
				WhitelistedProxyDomains = (from d in MultiValueSettingParser.ParseCommaDelimitedListString(newCsv)
					select d.ToLower()).ToArray();
			});
		}

		public static string ReplaceDomain(HttpRequest request, string s)
		{
			return ReplaceDomain(request.Headers["Arkiv-CNP-Url"], s);
		}

		public static string ReplaceDomain(string arkivCnProxyUrl, string s)
		{
			string proxyHost;
			if (EnableProxyUrlDetection && IsProxiedChinaRequest(arkivCnProxyUrl, out proxyHost))
			{
				char[] dotSeparators = new char[1] { '.' };
				string[] proxyHostComponents = proxyHost.Split(dotSeparators);
				string topProxyDomain = "." + string.Join(".", proxyHostComponents.Where((string source, int index) => index != 0));
				string tld = ArkivEnvironment.Domain;
				if (!tld.StartsWith("."))
				{
					tld = "." + tld;
				}
				s = s.Replace(tld, topProxyDomain);
			}
			return s;
		}

		public static bool IsProxiedChinaRequest(HttpRequest request, out string proxyHost)
		{
			return IsProxiedChinaRequest(request.Headers["Arkiv-CNP-Url"], out proxyHost);
		}

		public static bool IsProxiedChinaRequest(string arkivCnProxyUrl, out string proxyHost)
		{
			proxyHost = null;
			Uri proxyUrl;
			if (Uri.TryCreate(arkivCnProxyUrl, UriKind.Absolute, out proxyUrl))
			{
				proxyHost = proxyUrl.Host;
				return WhitelistedProxyDomains.Any((string whitelistedProxyDomain) => proxyUrl.Host.EndsWith(whitelistedProxyDomain));
			}
			return false;
		}
	}
}
