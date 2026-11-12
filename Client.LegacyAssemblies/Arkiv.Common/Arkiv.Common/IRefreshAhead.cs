using System;

namespace Arkiv.Common
{
	public interface IRefreshAhead<T>
	{
		T Value { get; }

		void Refresh();

		void SetRefreshInterval(TimeSpan newRefreshInterval);
	}
}
