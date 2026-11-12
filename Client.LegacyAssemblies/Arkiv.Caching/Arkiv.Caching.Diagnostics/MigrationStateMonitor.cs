using System;
using Arkiv.Instrumentation;

namespace Arkiv.Caching.Diagnostics
{
	internal class MigrationStateMonitor : IMigrationStateMonitor
	{
		private const string _Category = "Arkiv.Caching.MigrationSharedCacheClientStates";

		private readonly ICounterRegistry _CounterRegistry;

		public MigrationStateMonitor(ICounterRegistry counterRegistry)
		{
			if (counterRegistry == null)
			{
				throw new ArgumentNullException("counterRegistry");
			}
			_CounterRegistry = counterRegistry;
		}

		public void RecordMigrationState(string metricsIdentifier, MigrationStateChange migrationStateChange)
		{
			if (!string.IsNullOrWhiteSpace(metricsIdentifier) && IsValid(migrationStateChange))
			{
				_CounterRegistry.GetRawValueCounter("Arkiv.Caching.MigrationSharedCacheClientStates", "SourceMigrationState", metricsIdentifier).Set((long)migrationStateChange.SourceState);
				_CounterRegistry.GetRawValueCounter("Arkiv.Caching.MigrationSharedCacheClientStates", "DestinationMigrationState", metricsIdentifier).Set((long)migrationStateChange.DestinationState);
			}
		}

		private bool IsValid(MigrationStateChange stateChange)
		{
			bool num = Enum.IsDefined(typeof(MigrationState), stateChange.SourceState);
			bool flag = Enum.IsDefined(typeof(MigrationState), stateChange.DestinationState);
			if (num && flag)
			{
				return !stateChange.IsSourceAndDestinationStateSame;
			}
			return false;
		}
	}
}
