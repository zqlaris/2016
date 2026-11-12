using System;
using Arkiv.Caching.Interfaces;
using Arkiv.Instrumentation;

namespace Arkiv.Caching.Diagnostics
{
	public class CachePerformanceCounters : IArkivCacheListener
	{
		private const string _PerformanceCategory = "Arkiv.Caching";

		private readonly string _InstanceName;

		private readonly ICounterRegistry _CounterRegistry;

		private readonly IRawValueCounter _Queries;

		private readonly IRateOfCountsPerSecondCounter _QueriesPerSec;

		private readonly IRawValueCounter _Misses;

		private readonly IRateOfCountsPerSecondCounter _MissesPerSec;

		private readonly IRawValueCounter _Hits;

		private readonly IRateOfCountsPerSecondCounter _HitsPerSec;

		private readonly IFractionCounter _HitRatio;

		public CachePerformanceCounters(ICounterRegistry counterRegistry, string instanceName = "Total")
		{
			if (counterRegistry == null)
			{
				throw new ArgumentNullException("counterRegistry");
			}
			_CounterRegistry = counterRegistry;
			if (instanceName == null)
			{
				throw new ArgumentNullException("instanceName");
			}
			_InstanceName = instanceName;
			_Queries = _CounterRegistry.GetRawValueCounter("Arkiv.Caching", "Queries", _InstanceName);
			_QueriesPerSec = _CounterRegistry.GetRateOfCountsPerSecondCounter("Arkiv.Caching", "Queries/s", _InstanceName);
			_Misses = _CounterRegistry.GetRawValueCounter("Arkiv.Caching", "Misses", _InstanceName);
			_MissesPerSec = _CounterRegistry.GetRateOfCountsPerSecondCounter("Arkiv.Caching", "Misses/s", _InstanceName);
			_Hits = _CounterRegistry.GetRawValueCounter("Arkiv.Caching", "Hits", _InstanceName);
			_HitsPerSec = _CounterRegistry.GetRateOfCountsPerSecondCounter("Arkiv.Caching", "Hits/s", _InstanceName);
			_HitRatio = _CounterRegistry.GetFractionCounter("Arkiv.Caching", "Hit Ratio", _InstanceName);
		}

		public void OnQuery()
		{
			_Queries.Increment();
			_QueriesPerSec.Increment();
			_HitRatio.IncrementBase();
		}

		public void OnQuery(string entityType)
		{
			OnQuery(entityType, 1);
		}

		public void OnHit(string entityType)
		{
			OnHit(entityType, 1);
		}

		public void OnMiss(string entityType)
		{
			OnMiss(entityType, 1);
		}

		public void OnQuery(string entityType, int count)
		{
			_Queries.IncrementBy((long)count);
			_QueriesPerSec.IncrementBy((long)count);
			_HitRatio.IncrementBase();
		}

		public void OnHit(string entityType, int count)
		{
			_Hits.IncrementBy((long)count);
			_HitsPerSec.IncrementBy((long)count);
			_HitRatio.Increment();
		}

		public void OnMiss(string entityType, int count)
		{
			_Misses.IncrementBy((long)count);
			_MissesPerSec.IncrementBy((long)count);
		}
	}
}
