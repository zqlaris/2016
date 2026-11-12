using System;

namespace Arkiv.Sentinels.CircuitBreakerPolicy
{
	public interface IDefaultCircuitBreakerPolicyConfig
	{
		TimeSpan RetryInterval { get; }

		int FailuresAllowedBeforeTrip { get; }
	}
}
