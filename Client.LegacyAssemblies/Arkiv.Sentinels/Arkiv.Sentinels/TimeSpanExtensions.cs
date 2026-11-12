using System;

namespace Arkiv.Sentinels
{
	internal static class TimeSpanExtensions
	{
		public static TimeSpan Multiply(this TimeSpan multiplicand, double multiplier)
		{
			return TimeSpan.FromTicks((long)((double)multiplicand.Ticks * multiplier));
		}
	}
}
