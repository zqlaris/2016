namespace Arkiv.Caching
{
	public interface ILookupCacheFactory
	{
		ILookupCache GetLookupCache(ICacheInfo cacheInfo);
	}
}
