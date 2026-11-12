using System;
using System.ComponentModel;

namespace Arkiv.ServiceDiscovery.Properties
{
	internal interface ISettings : INotifyPropertyChanged
	{
		TimeSpan ConsulLongPollingMaxWaitTime { get; }

		string ConsulAddress { get; }

		TimeSpan ConsulBackoffBase { get; }

		TimeSpan MaximumConsulBackoff { get; }
	}
}
