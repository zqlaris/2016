using System.Net;

namespace Arkiv.ServiceDiscovery
{
	internal class DnsWrapper : IDns
	{
		public string GetHostName()
		{
			return Dns.GetHostName();
		}

		public IPHostEntry GetHostEntry(string hostNameOrAddress)
		{
			return Dns.GetHostEntry(hostNameOrAddress);
		}
	}
}
