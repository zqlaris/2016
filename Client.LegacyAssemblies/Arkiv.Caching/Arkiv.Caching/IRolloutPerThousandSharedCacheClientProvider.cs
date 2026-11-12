using Arkiv.Caching.Shared;

namespace Arkiv.Caching
{
	internal interface IRolloutPerThousandSharedCacheClientProvider
	{
		ISharedCacheClient GetCacheClientForMigrationStateChange(MigrationStateChange migrationStateChange, ISharedCacheClient sourceCacheClient, ISharedCacheClient destinationCacheClient);
	}
}
