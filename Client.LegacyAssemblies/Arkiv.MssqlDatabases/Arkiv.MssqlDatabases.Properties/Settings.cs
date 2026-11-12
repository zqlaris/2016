using System.CodeDom.Compiler;
using System.Collections.Concurrent;
using System.ComponentModel;
using System.Configuration;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Runtime.CompilerServices;
using Arkiv.Configuration;

namespace Arkiv.MssqlDatabases.Properties
{
	[SettingsProvider(typeof(Provider))]
	[ExcludeFromCodeCoverage]
	[CompilerGenerated]
	[GeneratedCode("Microsoft.VisualStudio.Editors.SettingsDesigner.SettingsSingleFileGenerator", "15.9.0.0")]
	internal sealed class Settings : ApplicationSettingsBase
	{
		private readonly ConcurrentDictionary<string, object> _Properties = new ConcurrentDictionary<string, object>();

		private static Settings defaultInstance = (Settings)SettingsBase.Synchronized(new Settings());

		public override object this[string propertyName]
		{
			get
			{
				return _Properties.GetOrAdd(propertyName, (string propName) => base[propName]);
			}
			set
			{
				base[propertyName] = value;
			}
		}

		public static Settings Default
		{
			get
			{
				return defaultInstance;
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAds
		{
			get
			{
				return (string)this["ArkivAds"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAggregation
		{
			get
			{
				return (string)this["ArkivAggregation"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAssetCounters
		{
			get
			{
				return (string)this["ArkivAssetCounters"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAssetCreations
		{
			get
			{
				return (string)this["ArkivAssetCreations"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAssetHashes
		{
			get
			{
				return (string)this["ArkivAssetHashes"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAssetMedia
		{
			get
			{
				return (string)this["ArkivAssetMedia"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAssets
		{
			get
			{
				return (string)this["ArkivAssets"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAssetSales
		{
			get
			{
				return (string)this["ArkivAssetSales"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAssetSecurity
		{
			get
			{
				return (string)this["ArkivAssetSecurity"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAssetSets
		{
			get
			{
				return (string)this["ArkivAssetSets"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAssetStatistics
		{
			get
			{
				return (string)this["ArkivAssetStatistics"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAssetStatisticsAggregation
		{
			get
			{
				return (string)this["ArkivAssetStatisticsAggregation"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAvatars
		{
			get
			{
				return (string)this["ArkivAvatars"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivBilling
		{
			get
			{
				return (string)this["ArkivBilling"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivChat
		{
			get
			{
				return (string)this["ArkivChat"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivClientSettings
		{
			get
			{
				return (string)this["ArkivClientSettings"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivContent
		{
			get
			{
				return (string)this["ArkivContent"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivContentRatings
		{
			get
			{
				return (string)this["ArkivContentRatings"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivContests
		{
			get
			{
				return (string)this["ArkivContests"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivCurrency
		{
			get
			{
				return (string)this["ArkivCurrency"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivDemographics
		{
			get
			{
				return (string)this["ArkivDemographics"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivDeployments
		{
			get
			{
				return (string)this["ArkivDeployments"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivDeveloperProducts
		{
			get
			{
				return (string)this["ArkivDeveloperProducts"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivDistribution
		{
			get
			{
				return (string)this["ArkivDistribution"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivEconomy
		{
			get
			{
				return (string)this["ArkivEconomy"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivEphemeralCounters
		{
			get
			{
				return (string)this["ArkivEphemeralCounters"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivFeeds
		{
			get
			{
				return (string)this["ArkivFeeds"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivFiles
		{
			get
			{
				return (string)this["ArkivFiles"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivGameCounters
		{
			get
			{
				return (string)this["ArkivGameCounters"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivGamePasses
		{
			get
			{
				return (string)this["ArkivGamePasses"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivGamePersistence
		{
			get
			{
				return (string)this["ArkivGamePersistence"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivGames
		{
			get
			{
				return (string)this["ArkivGames"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivGameService
		{
			get
			{
				return (string)this["ArkivGameService"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivGamesRecentlyVisited
		{
			get
			{
				return (string)this["ArkivGamesRecentlyVisited"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivGroups
		{
			get
			{
				return (string)this["ArkivGroups"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivInfrastructure
		{
			get
			{
				return (string)this["ArkivInfrastructure"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivInfrastructureAudit
		{
			get
			{
				return (string)this["ArkivInfrastructureAudit"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivInteractionCounters
		{
			get
			{
				return (string)this["ArkivInteractionCounters"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivLatencyMeasurements
		{
			get
			{
				return (string)this["ArkivLatencyMeasurements"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivMaintenance
		{
			get
			{
				return (string)this["ArkivMaintenance"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivMarketing
		{
			get
			{
				return (string)this["ArkivMarketing"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivMetrics
		{
			get
			{
				return (string)this["ArkivMetrics"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivMetricsClient
		{
			get
			{
				return (string)this["ArkivMetricsClient"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivMetricsSandbox
		{
			get
			{
				return (string)this["ArkivMetricsSandbox"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivModeration
		{
			get
			{
				return (string)this["ArkivModeration"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivModerationNew
		{
			get
			{
				return (string)this["ArkivModerationNew"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivObservation
		{
			get
			{
				return (string)this["ArkivObservation"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivPermissions
		{
			get
			{
				return (string)this["ArkivPermissions"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivPoints
		{
			get
			{
				return (string)this["ArkivPoints"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivPremiumFeatures
		{
			get
			{
				return (string)this["ArkivPremiumFeatures"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivPresence
		{
			get
			{
				return (string)this["ArkivPresence"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivReporting
		{
			get
			{
				return (string)this["ArkivReporting"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivSegmentation
		{
			get
			{
				return (string)this["ArkivSegmentation"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivServices
		{
			get
			{
				return (string)this["ArkivServices"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivShops
		{
			get
			{
				return (string)this["ArkivShops"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivStatistics
		{
			get
			{
				return (string)this["ArkivStatistics"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivStudio
		{
			get
			{
				return (string)this["ArkivStudio"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivThumbnails
		{
			get
			{
				return (string)this["ArkivThumbnails"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivTimeSeries
		{
			get
			{
				return (string)this["ArkivTimeSeries"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivTrades
		{
			get
			{
				return (string)this["ArkivTrades"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivTransactionHistory
		{
			get
			{
				return (string)this["ArkivTransactionHistory"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivUniverses
		{
			get
			{
				return (string)this["ArkivUniverses"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivUserAssetEscrows
		{
			get
			{
				return (string)this["ArkivUserAssetEscrows"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivUserAssets
		{
			get
			{
				return (string)this["ArkivUserAssets"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivUserCounters
		{
			get
			{
				return (string)this["ArkivUserCounters"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivUsers
		{
			get
			{
				return (string)this["ArkivUsers"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivUserSettings
		{
			get
			{
				return (string)this["ArkivUserSettings"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivVersions
		{
			get
			{
				return (string)this["ArkivVersions"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivVoting
		{
			get
			{
				return (string)this["ArkivVoting"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivVotingCounters
		{
			get
			{
				return (string)this["ArkivVotingCounters"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string Arkiv
		{
			get
			{
				return (string)this["Arkiv"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAuthentication
		{
			get
			{
				return (string)this["ArkivAuthentication"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivSystemEvents
		{
			get
			{
				return (string)this["ArkivSystemEvents"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAbTesting
		{
			get
			{
				return (string)this["ArkivAbTesting"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivXbox
		{
			get
			{
				return (string)this["ArkivXbox"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAssetNamespaces
		{
			get
			{
				return (string)this["ArkivAssetNamespaces"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivShowcases
		{
			get
			{
				return (string)this["ArkivShowcases"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivDeviceVoting
		{
			get
			{
				return (string)this["ArkivDeviceVoting"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivCurrencyBudgets
		{
			get
			{
				return (string)this["ArkivCurrencyBudgets"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivFilesV2
		{
			get
			{
				return (string)this["ArkivFilesV2"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivPushNotifications
		{
			get
			{
				return (string)this["ArkivPushNotifications"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivNotifications
		{
			get
			{
				return (string)this["ArkivNotifications"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivGroupRoleSets
		{
			get
			{
				return (string)this["ArkivGroupRoleSets"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivGroupPosts
		{
			get
			{
				return (string)this["ArkivGroupPosts"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivIPAddresses
		{
			get
			{
				return (string)this["ArkivIPAddresses"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivUserPrivacy
		{
			get
			{
				return (string)this["ArkivUserPrivacy"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivClickThroughAgreements
		{
			get
			{
				return (string)this["ArkivClickThroughAgreements"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivUserStatuses
		{
			get
			{
				return (string)this["ArkivUserStatuses"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivEmailAddresses
		{
			get
			{
				return (string)this["ArkivEmailAddresses"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivUserRetention
		{
			get
			{
				return (string)this["ArkivUserRetention"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivFriendships
		{
			get
			{
				return (string)this["ArkivFriendships"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivFollowings
		{
			get
			{
				return (string)this["ArkivFollowings"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivFriendRequests
		{
			get
			{
				return (string)this["ArkivFriendRequests"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivMacAddresses
		{
			get
			{
				return (string)this["ArkivMacAddresses"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAccountSecurity
		{
			get
			{
				return (string)this["ArkivAccountSecurity"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivLocales
		{
			get
			{
				return (string)this["ArkivLocales"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivRoles
		{
			get
			{
				return (string)this["ArkivRoles"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAccounts
		{
			get
			{
				return (string)this["ArkivAccounts"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivFileLocations
		{
			get
			{
				return (string)this["ArkivFileLocations"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivPlaceShowcases
		{
			get
			{
				return (string)this["ArkivPlaceShowcases"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivGroupMembership
		{
			get
			{
				return (string)this["ArkivGroupMembership"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivUserAssetOptions
		{
			get
			{
				return (string)this["ArkivUserAssetOptions"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivUserAssetExpirations
		{
			get
			{
				return (string)this["ArkivUserAssetExpirations"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivGroupCounters
		{
			get
			{
				return (string)this["ArkivGroupCounters"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivClans
		{
			get
			{
				return (string)this["ArkivClans"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivUsersAudit
		{
			get
			{
				return (string)this["ArkivUsersAudit"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAccountPhoneNumbersAudit
		{
			get
			{
				return (string)this["ArkivAccountPhoneNumbersAudit"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivTwoStepVerificationSettingsAudit
		{
			get
			{
				return (string)this["ArkivTwoStepVerificationSettingsAudit"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivCollectibles
		{
			get
			{
				return (string)this["ArkivCollectibles"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivGameAttributes
		{
			get
			{
				return (string)this["ArkivGameAttributes"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivItemStatusesAudit
		{
			get
			{
				return (string)this["ArkivItemStatusesAudit"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAccountPinHashesAudit
		{
			get
			{
				return (string)this["ArkivAccountPinHashesAudit"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivBadgesV2
		{
			get
			{
				return (string)this["ArkivBadgesV2"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivGroupMembershipRequests
		{
			get
			{
				return (string)this["ArkivGroupMembershipRequests"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAssetsAudit
		{
			get
			{
				return (string)this["ArkivAssetsAudit"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivComments
		{
			get
			{
				return (string)this["ArkivComments"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivUserFeeds
		{
			get
			{
				return (string)this["ArkivUserFeeds"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivBrowserTrackers
		{
			get
			{
				return (string)this["ArkivBrowserTrackers"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivGameTemplates
		{
			get
			{
				return (string)this["ArkivGameTemplates"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivMessages
		{
			get
			{
				return (string)this["ArkivMessages"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivRobuxStipends
		{
			get
			{
				return (string)this["ArkivRobuxStipends"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAccountLocalization
		{
			get
			{
				return (string)this["ArkivAccountLocalization"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivFavorites
		{
			get
			{
				return (string)this["ArkivFavorites"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivPermissionLists
		{
			get
			{
				return (string)this["ArkivPermissionLists"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAssetVersions
		{
			get
			{
				return (string)this["ArkivAssetVersions"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivLocalization
		{
			get
			{
				return (string)this["ArkivLocalization"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivFavoriteCounters
		{
			get
			{
				return (string)this["ArkivFavoriteCounters"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivDailyLogins
		{
			get
			{
				return (string)this["ArkivDailyLogins"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivTranslation
		{
			get
			{
				return (string)this["ArkivTranslation"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivBillingAuditLogs
		{
			get
			{
				return (string)this["ArkivBillingAuditLogs"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivBundles
		{
			get
			{
				return (string)this["ArkivBundles"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivEventsIngestValidation
		{
			get
			{
				return (string)this["ArkivEventsIngestValidation"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivModerationReportsAudit
		{
			get
			{
				return (string)this["ArkivModerationReportsAudit"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivContacts
		{
			get
			{
				return (string)this["ArkivContacts"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivUserDataProtection
		{
			get
			{
				return (string)this["ArkivUserDataProtection"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAccountsAudit
		{
			get
			{
				return (string)this["ArkivAccountsAudit"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAccoutrements
		{
			get
			{
				return (string)this["ArkivAccoutrements"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivPromotionChannels
		{
			get
			{
				return (string)this["ArkivPromotionChannels"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivMachineLearningModels
		{
			get
			{
				return (string)this["ArkivMachineLearningModels"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAccountCountriesAudit
		{
			get
			{
				return (string)this["ArkivAccountCountriesAudit"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivTranslationStorage
		{
			get
			{
				return (string)this["ArkivTranslationStorage"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAssetDetailsQuality
		{
			get
			{
				return (string)this["ArkivAssetDetailsQuality"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivInGameContentTables
		{
			get
			{
				return (string)this["ArkivInGameContentTables"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAccountLocalesAudit
		{
			get
			{
				return (string)this["ArkivAccountLocalesAudit"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivTeamOwnership
		{
			get
			{
				return (string)this["ArkivTeamOwnership"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivFriendshipSources
		{
			get
			{
				return (string)this["ArkivFriendshipSources"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivLeasedLocks
		{
			get
			{
				return (string)this["ArkivLeasedLocks"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivModerationAutomationAudit
		{
			get
			{
				return (string)this["ArkivModerationAutomationAudit"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAccountPasswordHashes
		{
			get
			{
				return (string)this["ArkivAccountPasswordHashes"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivXboxLiveAccounts
		{
			get
			{
				return (string)this["ArkivXboxLiveAccounts"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivFacebookAccounts
		{
			get
			{
				return (string)this["ArkivFacebookAccounts"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivStaticContent
		{
			get
			{
				return (string)this["ArkivStaticContent"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivBadges
		{
			get
			{
				return (string)this["ArkivBadges"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivUsernames
		{
			get
			{
				return (string)this["ArkivUsernames"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivThemesV2
		{
			get
			{
				return (string)this["ArkivThemesV2"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivGameLocalization
		{
			get
			{
				return (string)this["ArkivGameLocalization"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivSurveyResponses
		{
			get
			{
				return (string)this["ArkivSurveyResponses"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivRatings
		{
			get
			{
				return (string)this["ArkivRatings"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivRatingsAudit
		{
			get
			{
				return (string)this["ArkivRatingsAudit"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivSurveys
		{
			get
			{
				return (string)this["ArkivSurveys"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivMatchmaking
		{
			get
			{
				return (string)this["ArkivMatchmaking"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivIdentities
		{
			get
			{
				return (string)this["ArkivIdentities"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivChatParticipants
		{
			get
			{
				return (string)this["ArkivChatParticipants"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivModerationPolicy
		{
			get
			{
				return (string)this["ArkivModerationPolicy"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivRules
		{
			get
			{
				return (string)this["ArkivRules"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivTranslationAudit
		{
			get
			{
				return (string)this["ArkivTranslationAudit"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivItemTags
		{
			get
			{
				return (string)this["ArkivItemTags"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivCurrencyRobuxHolds
		{
			get
			{
				return (string)this["ArkivCurrencyRobuxHolds"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivCanonicalImages
		{
			get
			{
				return (string)this["ArkivCanonicalImages"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivTranslationAnalyticsReports
		{
			get
			{
				return (string)this["ArkivTranslationAnalyticsReports"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivGiftCards
		{
			get
			{
				return (string)this["ArkivGiftCards"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivUGCValidation
		{
			get
			{
				return (string)this["ArkivUGCValidation"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAvatarEmotes
		{
			get
			{
				return (string)this["ArkivAvatarEmotes"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivItemManifolds
		{
			get
			{
				return (string)this["ArkivItemManifolds"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAssetFormats
		{
			get
			{
				return (string)this["ArkivAssetFormats"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivEngagementPayouts
		{
			get
			{
				return (string)this["ArkivEngagementPayouts"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[SpecialSetting(SpecialSetting.ConnectionString)]
		public string ArkivAvatarPolicies
		{
			get
			{
				return (string)this["ArkivAvatarPolicies"];
			}
		}

		internal Settings()
		{
			base.PropertyChanged += delegate(object sender, PropertyChangedEventArgs args)
			{
				object value;
				_Properties.TryRemove(args.PropertyName, out value);
			};
		}

		protected override void OnSettingsLoaded(object sender, SettingsLoadedEventArgs e)
		{
			base.OnSettingsLoaded(sender, e);
			Provider.RegisterSettings(e, this);
		}
	}
}
