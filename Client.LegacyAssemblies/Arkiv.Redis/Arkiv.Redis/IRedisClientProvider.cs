namespace Arkiv.Redis
{
	public interface IRedisClientProvider
	{
		IRedisClient Client { get; }
	}
}
