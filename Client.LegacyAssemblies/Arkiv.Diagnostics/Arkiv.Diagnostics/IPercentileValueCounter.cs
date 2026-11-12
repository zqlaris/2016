using System;

namespace Arkiv.Diagnostics
{
	public interface IPercentileValueCounter : IDisposable
	{
		void Sample(double value);
	}
}
