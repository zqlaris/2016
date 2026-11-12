using System.Diagnostics;

namespace Arkiv.Diagnostics
{
	internal interface ICounterDescriptor
	{
		CounterCreationData CounterCreationData { get; }
	}
}
