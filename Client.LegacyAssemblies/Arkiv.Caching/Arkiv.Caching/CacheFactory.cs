using Arkiv.Caching.DotNet;
using Arkiv.Caching.MemCached;
using Arkiv.Instrumentation;

namespace Arkiv.Caching
{
	internal class CacheFactory
	{
		private static readonly LocalCache _LocalCache = new DotNetCoreCache(StaticCounterRegistry.Instance, true);

		private static readonly LocalBackedByMemcache _LocalBackedBySharedCache = new LocalBackedByMemcache();

		public static ArkivCache GetCacheForEntity(ICacheInfo cacheInfo)
		{
			IEntityRampUpAuthority instance = EntityRampUpAuthority.GetInstance();
			if (instance != null && instance.IsRemoteCacheable(cacheInfo.EntityType))
			{
				return _LocalBackedBySharedCache;
			}
			return _LocalCache;
		}

		public static LocalCache GetLocalCache()
		{
			return _LocalCache;
		}
	}
}
