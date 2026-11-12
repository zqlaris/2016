using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Reflection;
using System.Threading;
using System.Threading.Tasks;
using Arkiv.Instrumentation;
using Arkiv.Mssql;
using Arkiv.MssqlDatabases.Properties;

namespace Arkiv.MssqlDatabases
{
	public static class Extensions
	{
		private static readonly ConcurrentDictionary<ArkivDatabase, Func<string>> _ConnectionStringGetterCache = new ConcurrentDictionary<ArkivDatabase, Func<string>>();

		private static readonly DatabaseRegistry _DatabaseRegistry = new DatabaseRegistry(BuildDatabaseObserver);

		private static readonly Settings _Settings = Settings.Default;

		private static readonly Type _SettingsType = _Settings.GetType();

		private static readonly ConcurrentDictionary<ArkivDatabase, Func<TimeSpan>> _CommandTimeoutGetterCache = new ConcurrentDictionary<ArkivDatabase, Func<TimeSpan>>();

		private static readonly TimeoutSettings _TimeoutSettings = TimeoutSettings.Default;

		private static readonly Type _TimeoutSettingsType = _TimeoutSettings.GetType();

		private static readonly Func<TimeSpan> _DefaultDatabaseTimeoutGetter = () => _TimeoutSettings.DefaultCommandTimeout;

		public static Func<string> GetConnectionStringGetter(this ArkivDatabase arkivDatabase)
		{
			return _ConnectionStringGetterCache.GetOrAdd(arkivDatabase, delegate(ArkivDatabase db)
			{
				string text = db.ToString();
				PropertyInfo property = _SettingsType.GetProperty(text);
				if (property == null)
				{
					throw new Exception("ConnectionString for database " + text + " is not defined.");
				}
				MethodInfo getMethod = property.GetGetMethod();
				Func<Settings, string> rawDelegate = (Func<Settings, string>)getMethod.CreateDelegate(typeof(Func<Settings, string>));
				return () => rawDelegate(_Settings);
			});
		}

		public static Func<TimeSpan> GetCommandTimeoutGetter(this ArkivDatabase arkivDatabase)
		{
			return _CommandTimeoutGetterCache.GetOrAdd(arkivDatabase, delegate(ArkivDatabase db)
			{
				string name = db.ToString();
				PropertyInfo property = _TimeoutSettingsType.GetProperty(name);
				if (property == null)
				{
					return _DefaultDatabaseTimeoutGetter;
				}
				MethodInfo getMethod = property.GetGetMethod();
				Func<TimeoutSettings, TimeSpan> rawDelegate = (Func<TimeoutSettings, TimeSpan>)getMethod.CreateDelegate(typeof(Func<TimeoutSettings, TimeSpan>));
				return () => rawDelegate(_TimeoutSettings);
			});
		}

		public static void ValidateDatabase(this ArkivDatabase arkivDatabase)
		{
			_DatabaseRegistry.GetDatabase(arkivDatabase);
		}

		public static int ExecuteNonQuery(this ArkivDatabase arkivDatabase, string commandText, SqlParameter[] sqlParameters, CommandType commandType = CommandType.StoredProcedure, int? commandTimeout = null, ApplicationIntent? applicationIntent = null)
		{
			return _DatabaseRegistry.GetDatabase(arkivDatabase).ExecuteNonQuery(commandText, sqlParameters, commandType, commandTimeout, applicationIntent);
		}

		public static Task<int> ExecuteNonQueryAsync(this ArkivDatabase arkivDatabase, string commandText, SqlParameter[] sqlParameters, CommandType commandType = CommandType.StoredProcedure, CancellationToken cancellationToken = default(CancellationToken), int? commandTimeout = null, ApplicationIntent? applicationIntent = null)
		{
			return _DatabaseRegistry.GetDatabase(arkivDatabase).ExecuteNonQueryAsync(commandText, sqlParameters, commandType, cancellationToken, commandTimeout, applicationIntent);
		}

		public static IEnumerable<IDictionary<string, object>> ExecuteReader(this ArkivDatabase arkivDatabase, string commandText, SqlParameter[] sqlParameters, CommandType commandType = CommandType.StoredProcedure, int? commandTimeout = null, ApplicationIntent? applicationIntent = null)
		{
			return _DatabaseRegistry.GetDatabase(arkivDatabase).ExecuteReader(commandText, sqlParameters, commandType, commandTimeout, applicationIntent);
		}

		public static Task<IEnumerable<IDictionary<string, object>>> ExecuteReaderAsync(this ArkivDatabase arkivDatabase, string commandText, SqlParameter[] sqlParameters, CommandType commandType = CommandType.StoredProcedure, CancellationToken cancellationToken = default(CancellationToken), int? commandTimeout = null, ApplicationIntent? applicationIntent = null)
		{
			return _DatabaseRegistry.GetDatabase(arkivDatabase).ExecuteReaderAsync(commandText, sqlParameters, commandType, cancellationToken, commandTimeout, applicationIntent);
		}

		public static object ExecuteScalar(this ArkivDatabase arkivDatabase, string commandText, SqlParameter[] sqlParameters, CommandType commandType = CommandType.StoredProcedure, int? commandTimeout = null, ApplicationIntent? applicationIntent = null)
		{
			return _DatabaseRegistry.GetDatabase(arkivDatabase).ExecuteScalar(commandText, sqlParameters, commandType, commandTimeout, applicationIntent);
		}

		public static Task<object> ExecuteScalarAsync(this ArkivDatabase arkivDatabase, string commandText, SqlParameter[] sqlParameters, CommandType commandType = CommandType.StoredProcedure, CancellationToken cancellationToken = default(CancellationToken), int? commandTimeout = null, ApplicationIntent? applicationIntent = null)
		{
			return _DatabaseRegistry.GetDatabase(arkivDatabase).ExecuteScalarAsync(commandText, sqlParameters, commandType, cancellationToken, commandTimeout, applicationIntent);
		}

		public static string GetConnectionString(this ArkivDatabase arkivDatabase)
		{
			return _DatabaseRegistry.GetDatabase(arkivDatabase).ConnectionString;
		}

		public static string GetConnectionStringForAsync(this ArkivDatabase arkivDatabase)
		{
			return _DatabaseRegistry.GetDatabase(arkivDatabase).ConnectionStringAsync;
		}

		public static TimeSpan GetCommandTimeout(this ArkivDatabase arkivDatabase)
		{
			return _DatabaseRegistry.GetDatabase(arkivDatabase).CommandTimeout;
		}

		public static string GetUtilizedConnectionString(this ArkivDatabase arkivDatabase, ApplicationIntent? applicationIntent)
		{
			return _DatabaseRegistry.GetDatabase(arkivDatabase).GetUtilizedConnectionString(applicationIntent);
		}

		public static string GetUtilizedConnectionStringForAsync(this ArkivDatabase arkivDatabase, ApplicationIntent? applicationIntent)
		{
			return _DatabaseRegistry.GetDatabase(arkivDatabase).GetUtilizedConnectionStringAsync(applicationIntent);
		}

		private static IDatabaseObserver BuildDatabaseObserver(IDatabase database)
		{
			//IL_0006: Unknown result type (might be due to invalid IL or missing references)
			//IL_000c: Expected O, but got Unknown
			return (IDatabaseObserver)new DatabaseObserver(database, StaticCounterRegistry.Instance);
		}
	}
}
