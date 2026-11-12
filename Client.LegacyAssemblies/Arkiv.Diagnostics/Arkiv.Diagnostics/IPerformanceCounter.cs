using System;

namespace Arkiv.Diagnostics
{
	public interface IPerformanceCounter : IDisposable
	{
		long Value { get; set; }

		void Increment();

		void IncrementBy(long value);

		void Reset();
	}
}
