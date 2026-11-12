using System;
using Arkiv.Configuration;
using Arkiv.Instrumentation;
using Arkiv.Redis.Lru.Properties;

namespace Arkiv.Redis.Lru
{
	[Obsolete("Use your own cluster instead")]
	internal static class RedisLruClient
	{
		private static IRedisClient _RedisClient;

		private static string _RedisEndpointsCsv;

		static RedisLruClient()
		{
			_RedisEndpointsCsv = "";
			Settings.Default.ReadValueAndMonitorChanges((Settings s) => s.SharedLruCacheRedisEndpointsCsv, delegate(string endpointsCsv)
			{
				if (!_RedisEndpointsCsv.Equals(endpointsCsv))
				{
					_RedisEndpointsCsv = endpointsCsv;
					string[] redisEndpoints = endpointsCsv.Split(new char[1] { ',' });
					if (_RedisClient == null)
					{
						_RedisClient = new RedisClient(StaticCounterRegistry.Instance, redisEndpoints, "Arkiv.Redis.Lru", null, new RedisClientOptions(null, null, null, true));
					}
					else
					{
						_RedisClient.Refresh(redisEndpoints);
					}
				}
			});
		}

		[Obsolete("Use your own cluster instead")]
		public static IRedisClient GetInstance()
		{
			return _RedisClient;
		}
	}
}
