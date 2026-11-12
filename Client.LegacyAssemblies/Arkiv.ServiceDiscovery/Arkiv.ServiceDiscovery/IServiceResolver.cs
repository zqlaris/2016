using System.Collections.Generic;
using System.ComponentModel;
using System.Net;

namespace Arkiv.ServiceDiscovery
{
	public interface IServiceResolver : INotifyPropertyChanged
	{
		ISet<IPEndPoint> EndPoints { get; }
	}
}
