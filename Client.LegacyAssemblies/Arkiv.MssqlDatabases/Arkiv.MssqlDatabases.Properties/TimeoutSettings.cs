using System;
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
	internal sealed class TimeoutSettings : ApplicationSettingsBase
	{
		private readonly ConcurrentDictionary<string, object> _Properties = new ConcurrentDictionary<string, object>();

		private static TimeoutSettings defaultInstance = (TimeoutSettings)SettingsBase.Synchronized(new TimeoutSettings());

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

		public static TimeoutSettings Default
		{
			get
			{
				return defaultInstance;
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[DefaultSettingValue("00:00:30")]
		public TimeSpan DefaultCommandTimeout
		{
			get
			{
				return (TimeSpan)this["DefaultCommandTimeout"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[DefaultSettingValue("00:00:30")]
		public TimeSpan ArkivGroups
		{
			get
			{
				return (TimeSpan)this["ArkivGroups"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[DefaultSettingValue("00:00:30")]
		public TimeSpan ArkivGroupCounters
		{
			get
			{
				return (TimeSpan)this["ArkivGroupCounters"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[DefaultSettingValue("00:00:30")]
		public TimeSpan ArkivGroupMembershipRequests
		{
			get
			{
				return (TimeSpan)this["ArkivGroupMembershipRequests"];
			}
		}

		[ApplicationScopedSetting]
		[DebuggerNonUserCode]
		[DefaultSettingValue("00:00:30")]
		public TimeSpan ArkivAccoutrements
		{
			get
			{
				return (TimeSpan)this["ArkivAccoutrements"];
			}
		}

		internal TimeoutSettings()
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
