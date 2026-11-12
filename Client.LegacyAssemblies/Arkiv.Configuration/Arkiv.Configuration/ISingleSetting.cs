using System.ComponentModel;

namespace Arkiv.Configuration
{
	public interface ISingleSetting<T> : INotifyPropertyChanged
	{
		T Value { get; }
	}
}
