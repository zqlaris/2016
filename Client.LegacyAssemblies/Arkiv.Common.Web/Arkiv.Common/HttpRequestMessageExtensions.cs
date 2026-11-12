using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.ServiceModel.Channels;
using System.Web;

namespace Arkiv.Common
{
	public static class HttpRequestMessageExtensions
	{
		private static readonly IIpResolver<HttpHeaderIpResolverModel> _IpResolver = new HttpHeaderIpResolver();

		public static string GetClientIpAddress(this HttpRequestMessage request)
		{
			if (request.Properties.ContainsKey("MS_HttpContext"))
			{
				return ((HttpContextWrapper)request.Properties["MS_HttpContext"]).GetOriginIP();
			}
			if (request.Properties.ContainsKey(RemoteEndpointMessageProperty.Name))
			{
				RemoteEndpointMessageProperty prop = (RemoteEndpointMessageProperty)request.Properties[RemoteEndpointMessageProperty.Name];
				IEnumerable<string> xForwardedForHeaderValues;
				request.Headers.TryGetValues("X-Forwarded-For", out xForwardedForHeaderValues);
				string xForwardedForHeader = xForwardedForHeaderValues.FirstOrDefault();
				IEnumerable<string> xRealIpHeaderValues;
				request.Headers.TryGetValues("X-Real-IP", out xRealIpHeaderValues);
				string xRealIpHeader = xRealIpHeaderValues.FirstOrDefault();
				IEnumerable<string> xArkivProxiedForHeaderValues;
				request.Headers.TryGetValues("Arkiv-Proxied-IP", out xArkivProxiedForHeaderValues);
				string xArkivProxiedForHeader = xArkivProxiedForHeaderValues.FirstOrDefault();
				return _IpResolver.Resolve(new HttpHeaderIpResolverModel
				{
					UserHostAddress = prop.Address,
					ForwardedFor = xForwardedForHeader,
					DosArrestRealIpHeaderName = xRealIpHeader,
					ArkivProxiedFor = xArkivProxiedForHeader
				}).ToString();
			}
			return null;
		}
	}
}
