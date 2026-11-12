using StackExchange.Redis;

namespace Arkiv.Redis
{
	public delegate void DatabaseAction(IDatabase database);
	public delegate TResult DatabaseAction<out TResult>(IDatabase database);
}
