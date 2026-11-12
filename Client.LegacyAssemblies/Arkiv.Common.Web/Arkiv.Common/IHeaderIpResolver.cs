using System.Collections.Generic;
using System.Net;

namespace Arkiv.Common
{
	public interface IHeaderIpResolver
	{
		IPAddress Resolve(string remoteIpAddress, IDictionary<string, string> headers);
	}
}
