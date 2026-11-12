namespace Arkiv.Caching.Interfaces
{
	public interface IArkivCacheListener
	{
		void OnQuery(string entityType);

		void OnQuery(string entityType, int count);

		void OnHit(string entityType);

		void OnHit(string entityType, int count);

		void OnMiss(string entityType);

		void OnMiss(string entityType, int count);
	}
}
