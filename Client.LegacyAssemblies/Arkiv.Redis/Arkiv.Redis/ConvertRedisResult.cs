using StackExchange.Redis;

namespace Arkiv.Redis
{
	public delegate TResult ConvertRedisResult<out TResult>(RedisResult redisResult);
}
