using Arkiv.Caching.Shared;

namespace Arkiv.Caching
{
	public interface IMemcachedGroupCacheClientProvider
	{
		ISharedCacheClient GetCacheClientForGroup(string name);
	}
}
