using System.Web;

namespace Arkiv.Common
{
	public interface IHttpRequestProtocolResolver : IRequestProtocolResolver<HttpRequest>, IRequestProtocolResolver<HttpRequestBase>
	{
	}
}
