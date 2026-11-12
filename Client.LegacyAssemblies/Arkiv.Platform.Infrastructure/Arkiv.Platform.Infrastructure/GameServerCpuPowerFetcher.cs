using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using Arkiv.Common;
using Arkiv.Configuration;
using Arkiv.MssqlDatabases;

namespace Arkiv.Platform.Infrastructure
{
	public class GameServerCpuPowerFetcher
	{
		private readonly RefreshAhead<IDictionary<string, int>> _GamesRelayIpAddressToCpuPowerMap;

		public GameServerCpuPowerFetcher()
		{
			_GamesRelayIpAddressToCpuPowerMap = RefreshAhead<IDictionary<string, int>>.ConstructAndPopulate(TimeSpan.FromSeconds(60.0), () => GetServerIpAddressToCpuPowerMap(58, ArkivEnvironment.Id));
		}

		public int GetGameServerCpuPower(string ipAddress)
		{
			int cpuPower;
			_GamesRelayIpAddressToCpuPowerMap.Value.TryGetValue(ipAddress, out cpuPower);
			return cpuPower;
		}

		private IDictionary<string, int> GetServerIpAddressToCpuPowerMap(int serverGroupId, int environmentId)
		{
			SqlParameter[] parameters = new SqlParameter[2]
			{
				new SqlParameter("@ServerGroupID", serverGroupId),
				new SqlParameter("@EnvironmentID", environmentId)
			};
			Dictionary<string, int> serverCpuPowerByIP = new Dictionary<string, int>();
			foreach (IDictionary<string, object> item in ((ArkivDatabase)94).ExecuteReader("Servers_GetRccServerIpAddressDataCenterIDTotalCPUPowerByServerGroupIDAndEnvironmentID", parameters, CommandType.StoredProcedure, (int?)null, (ApplicationIntent?)null))
			{
				string ipAddress = (string)item["IpAddress"];
				int? totalCpuPower = (int?)item["TotalCPUPower"];
				if (totalCpuPower.HasValue)
				{
					serverCpuPowerByIP.Add(ipAddress, totalCpuPower.Value);
				}
			}
			return serverCpuPowerByIP;
		}
	}
}
