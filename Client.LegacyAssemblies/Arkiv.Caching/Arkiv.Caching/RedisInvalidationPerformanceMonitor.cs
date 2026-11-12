using System;
using Arkiv.Instrumentation;

namespace Arkiv.Caching
{
	internal class RedisInvalidationPerformanceMonitor : IRedisInvalidationPerformanceMonitor
	{
		private readonly ICounterRegistry _CounterRegistry;

		private const string _PerformanceCategory = "Arkiv.CacheInvalidation.Redis";

		private static IRedisInvalidationPerformanceMonitor _Instance;

		private static readonly object _InstanceCreationLock = new object();

		private IRateOfCountsPerSecondCounter MessagesReceivedPerSecondInstrumentation { get; set; }

		public IRateOfCountsPerSecondCounter MessagesPublishedPerSecond { get; set; }

		public IRateOfCountsPerSecondCounter MessagesReceivedPerSecond { get; set; }

		public IRawValueCounter TotalMessagesPublished { get; set; }

		public IRawValueCounter TotalMessagesReceived { get; set; }

		private RedisInvalidationPerformanceMonitor(ICounterRegistry counterRegistry)
		{
			if (counterRegistry == null)
			{
				throw new ArgumentNullException("counterRegistry");
			}
			_CounterRegistry = counterRegistry;
			MessagesPublishedPerSecond = _CounterRegistry.GetRateOfCountsPerSecondCounter("Arkiv.CacheInvalidation.Redis", "MessagesPublishedPerSecond", (string)null);
			MessagesReceivedPerSecond = _CounterRegistry.GetRateOfCountsPerSecondCounter("Arkiv.CacheInvalidation.Redis", "MessagesReceivedPerSecond", (string)null);
			TotalMessagesPublished = _CounterRegistry.GetRawValueCounter("Arkiv.CacheInvalidation.Redis", "TotalMessagesPublished", (string)null);
			TotalMessagesReceived = _CounterRegistry.GetRawValueCounter("Arkiv.CacheInvalidation.Redis", "TotalMessagesReceived", (string)null);
		}

		public static IRedisInvalidationPerformanceMonitor GetInstance(Action<Exception> exceptionHandler)
		{
			if (_Instance == null)
			{
				lock (_InstanceCreationLock)
				{
					if (_Instance == null)
					{
						IRedisInvalidationPerformanceMonitor instance = null;
						try
						{
							instance = new RedisInvalidationPerformanceMonitor(StaticCounterRegistry.Instance);
						}
						catch (Exception obj)
						{
							exceptionHandler(obj);
						}
						_Instance = instance;
					}
				}
			}
			return _Instance;
		}

		public double GetMessagesReceivedPerSecond()
		{
			//IL_0006: Unknown result type (might be due to invalid IL or missing references)
			return ((CounterBase)MessagesReceivedPerSecond).GetLastFlushValue();
		}
	}
}
