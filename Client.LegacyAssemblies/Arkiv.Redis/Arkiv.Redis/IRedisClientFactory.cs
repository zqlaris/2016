using System;

namespace Arkiv.Redis
{
	public interface IRedisClientFactory
	{
		IRedisClient GetRedisClient(RedisEndpoints endpoints, Action<Action<RedisEndpoints>> monitorWireup, string performanceMonitorCategory, Action<Exception> errorHandler);
	}
}
