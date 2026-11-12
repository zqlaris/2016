using System;
using System.Collections.Generic;
using Arkiv.Mssql;

namespace Arkiv.MssqlDatabases
{
	public sealed class DatabaseRegistry : IDisposable
	{
		private readonly Func<IDatabase, IDatabaseObserver> _DatabaseObserverBuilder;

		private readonly Dictionary<ArkivDatabase, Lazy<MonitoredGuardedDatabase>> _Databases = new Dictionary<ArkivDatabase, Lazy<MonitoredGuardedDatabase>>();

		private bool _IsDisposed;

		private static readonly TimeSpan _DefaultRetryInterval = TimeSpan.FromMilliseconds(100.0);

		public DatabaseRegistry(Func<IDatabase, IDatabaseObserver> databaseObserverBuilder)
		{
			if (databaseObserverBuilder == null)
			{
				throw new ArgumentNullException("databaseObserverBuilder");
			}
			_DatabaseObserverBuilder = databaseObserverBuilder;
			ArkivDatabase[] array = (ArkivDatabase[])Enum.GetValues(typeof(ArkivDatabase));
			foreach (ArkivDatabase arkivDatabase in array)
			{
				ArkivDatabase rd = arkivDatabase;
				Lazy<MonitoredGuardedDatabase> lazyDatabase = new Lazy<MonitoredGuardedDatabase>((Func<MonitoredGuardedDatabase>)(() => BuildDatabase(rd)));
				_Databases.Add(arkivDatabase, lazyDatabase);
			}
		}

		public void Dispose()
		{
			if (_IsDisposed)
			{
				return;
			}
			foreach (KeyValuePair<ArkivDatabase, Lazy<MonitoredGuardedDatabase>> database in _Databases)
			{
				Lazy<MonitoredGuardedDatabase> lazy = database.Value;
				if (lazy.IsValueCreated)
				{
					MonitoredGuardedDatabase value = lazy.Value;
					if (value != null)
					{
						((Database)value).Dispose();
					}
				}
			}
			_IsDisposed = true;
		}

		public Database GetDatabase(ArkivDatabase arkivDatabase)
		{
			Lazy<MonitoredGuardedDatabase> lazyDatabase;
			if (!_Databases.TryGetValue(arkivDatabase, out lazyDatabase))
			{
				throw new KeyNotFoundException("Unknown database: " + arkivDatabase);
			}
			return (Database)(object)lazyDatabase.Value;
		}

		private MonitoredGuardedDatabase BuildDatabase(ArkivDatabase arkivDatabase)
		{
			//IL_0028: Unknown result type (might be due to invalid IL or missing references)
			//IL_002e: Expected O, but got Unknown
			string text = arkivDatabase.ToString();
			Func<string> connectionStringGetter = arkivDatabase.GetConnectionStringGetter();
			Func<TimeSpan> commandTimeoutGetter = arkivDatabase.GetCommandTimeoutGetter();
			return new MonitoredGuardedDatabase(text, connectionStringGetter, commandTimeoutGetter, _DefaultRetryInterval, _DatabaseObserverBuilder);
		}
	}
}
