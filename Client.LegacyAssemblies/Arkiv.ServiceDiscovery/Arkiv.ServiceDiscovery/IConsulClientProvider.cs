using System.ComponentModel;
using Consul;

namespace Arkiv.ServiceDiscovery
{
	public interface IConsulClientProvider : INotifyPropertyChanged
	{
		IConsulClient Client { get; }
	}
}
