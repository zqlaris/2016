using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using Arkiv.Common;
using Arkiv.Configuration;
using Arkiv.MssqlDatabases;
using Arkiv.Platform.Infrastructure.Properties;

namespace Arkiv.Platform.Infrastructure
{
	internal static class GamesRelayDataAccess
	{
		private const string _DatacenterMapRedisKey = "GameRelayIpAddressToDatacenterIdDictionary";

		private static readonly RefreshAhead<IDictionary<string, int>> _GameRelayIpAddressToDatacenterIdDictionary = RefreshAhead<IDictionary<string, int>>.ConstructAndPopulate(Settings.Default.GameRelayIpAddressToDatacenterIdMapRefreshInterval, RefreshDatacenterData);

		internal static IDictionary<string, int> GameRelayIpAddressToDatacenterIdMap
		{
			get
			{
				return _GameRelayIpAddressToDatacenterIdDictionary.Value;
			}
		}

		internal static IDictionary<string, int> RefreshDatacenterData()
		{
			IDictionary<string, int> dictionary = InfrastructureCache.ReadDictionaryFromRedis("GameRelayIpAddressToDatacenterIdDictionary");
			if (dictionary == null)
			{
				dictionary = GetServerIpAddressToDatacenterIdMap(58, ArkivEnvironment.Id);
				InfrastructureCache.WriteDictionaryToRedis("GameRelayIpAddressToDatacenterIdDictionary", dictionary, Settings.Default.GameRelayIpAddressToDatacenterIdMapRefreshInterval);
			}
			return dictionary;
		}

		private static IDictionary<string, int> GetServerIpAddressToDatacenterIdMap(int serverGroupId, int environmentId)
		{
			SqlParameter[] parameters = new SqlParameter[2]
			{
				new SqlParameter("@ServerGroupID", serverGroupId),
				new SqlParameter("@EnvironmentID", environmentId)
			};
			IEnumerable<IDictionary<string, object>> enumerable = ((ArkivDatabase)94).ExecuteReader("Servers_GetRccServerIpAddressesToDataCenterIDByServerGroupIDAndEnvironmentID", parameters, CommandType.StoredProcedure, (int?)null, (ApplicationIntent?)null);
			Dictionary<string, int> dictionary = new Dictionary<string, int>();
			foreach (IDictionary<string, object> item in enumerable)
			{
				string ipAddress = (string)item["IpAddress"];
				int dataCenterId = (int)item["DataCenterID"];
				dictionary[ipAddress] = dataCenterId;
			}
			return dictionary;
		}
	}
}
