using System.Net;

namespace Arkiv.Common
{
	public interface IHttpHeaderIpResolver
	{
		IPAddress ResolveOriginIpFromRequestHeaders(string userHostAddress, string xForwardedForHeaderValue, string xRealIpHeaderValue, string arkivProxiedForHeaderValue);
	}
}
