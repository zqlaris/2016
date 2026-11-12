namespace Arkiv.Caching
{
	public interface IMigrationStateMonitor
	{
		void RecordMigrationState(string metricsIdentifier, MigrationStateChange migrationStateChange);
	}
}
