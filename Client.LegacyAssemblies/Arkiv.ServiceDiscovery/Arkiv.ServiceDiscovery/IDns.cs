using System.Net;

namespace Arkiv.ServiceDiscovery
{
	public interface IDns
	{
		string GetHostName();

		IPHostEntry GetHostEntry(string hostNameOrAddress);
	}
}
