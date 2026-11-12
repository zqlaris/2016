using System;
using System.Net;

namespace Arkiv.Common
{
	public interface IHttpSecureIpResolver
	{
		IPAddress ResolveOriginIpFromSecureIpHeaders(string trueIp, string proxyUrl, string nonce, bool enableHash, Tuple<string, string> hashAndKeyPair1, Tuple<string, string> hashAndKeyPair2);
	}
}
