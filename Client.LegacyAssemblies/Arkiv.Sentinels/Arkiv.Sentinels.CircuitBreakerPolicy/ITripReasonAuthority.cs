using System;

namespace Arkiv.Sentinels.CircuitBreakerPolicy
{
	public interface ITripReasonAuthority<in TExecutionContext>
	{
		bool IsReasonForTrip(TExecutionContext executionContext, Exception exception);
	}
}
