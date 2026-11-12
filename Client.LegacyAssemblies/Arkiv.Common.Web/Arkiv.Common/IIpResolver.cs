using System.Net;

namespace Arkiv.Common
{
	public interface IIpResolver<in TResolveFrom>
	{
		IPAddress Resolve(TResolveFrom data);
	}
}
