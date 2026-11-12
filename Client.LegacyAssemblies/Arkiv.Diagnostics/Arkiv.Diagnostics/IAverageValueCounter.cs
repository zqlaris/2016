using System;

namespace Arkiv.Diagnostics
{
	public interface IAverageValueCounter : IDisposable
	{
		void Sample(long value);
	}
}
