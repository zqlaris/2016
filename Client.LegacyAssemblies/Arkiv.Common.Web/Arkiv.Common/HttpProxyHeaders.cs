namespace Arkiv.Common
{
	public static class HttpProxyHeaders
	{
		public const string XForwardedForHeaderName = "X-Forwarded-For";

		public const string DosArrestRealIpHeaderName = "X-Real-IP";

		public const string XForwardedProtoHeaderName = "X-Forwarded-Proto";

		public const string ArkivEdgeProxyDate = "Arkiv-EP-Date";

		public const string ArkivEdgeProxyUrl = "Arkiv-EP-Url";

		public const string ArkivEdgeProxyTrueIp = "Arkiv-EP-True-IP";

		public const string ArkivEdgeProxySecure = "Arkiv-EP-Secure";

		public const string ArkivCnProxyDate = "Arkiv-CNP-Date";

		public const string ArkivCnProxyUrl = "Arkiv-CNP-Url";

		public const string ArkivCnProxyTrueIp = "Arkiv-CNP-True-IP";

		public const string ArkivCnProxySecure = "Arkiv-CNP-Secure";

		public const string ArkivCnProxySecure2 = "Arkiv-CNP-Secure2";

		public const string ArkivWhiteListProxiedIp = "Arkiv-Proxied-IP";
	}
}
