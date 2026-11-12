using Arkiv.Caching.Shared;

namespace Arkiv.Caching
{
	internal interface IMigrationSharedCacheClientProvider
	{
		ISharedCacheClient GetMigrationCacheClientForMigrationState(MigrationState migrationState, ISharedCacheClient sourceCacheClient, ISharedCacheClient destinationSharedCacheClient);
	}
}
