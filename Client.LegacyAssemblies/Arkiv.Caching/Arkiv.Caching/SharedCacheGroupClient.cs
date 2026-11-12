using BeIT.MemCached;
using Arkiv.Caching.Shared;
using Arkiv.EventLog;

namespace Arkiv.Caching
{
	internal class SharedCacheGroupClient : SharedCacheClient
	{
		public SharedCacheGroupClient(string groupName, string[] addresses, ILogger logger, IMemCachedClientSettings settings = null)
		{
			CreateMemcachedClient(addresses, string.Format("Arkiv MemcacheD {0}", groupName), logger, settings);
		}
	}
}
