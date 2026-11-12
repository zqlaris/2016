using System;
using System.Collections.Generic;
using Arkiv.Caching.Interfaces;
using Arkiv.EventLog;

namespace Arkiv.Caching
{
	public static class CacheInvalidatorFactory
	{
		public static ICacheInvalidator CreateCacheInvalidator(Func<IEnumerable<IRemoteCacheInvalidationSink>> listenerGetter, IRawMessageConsumer rawConsumer = null)
		{
			ILogger instance = StaticLoggerRegistry.Instance;
			IRedisInvalidationSettingsProvider instance2 = RedisInvalidationSettingsProvider.GetInstance();
			instance2.OnException += instance.Error;
			IRedisInvalidationPerformanceMonitor instance3 = RedisInvalidationPerformanceMonitor.GetInstance(instance.Error);
			return new RedisCacheInvalidator(listenerGetter, rawConsumer, instance2, instance3, instance.Error);
		}
	}
}
