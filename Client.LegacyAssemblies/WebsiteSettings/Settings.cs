using System.Configuration;

namespace Arkiv.WebsiteSettings.Properties
{
    [SettingsProvider(typeof(Arkiv.Configuration.Provider))]
    public sealed partial class Settings
    {
        protected override void OnSettingsLoaded(object sender, SettingsLoadedEventArgs e)
        {
            base.OnSettingsLoaded(sender, e);
            Arkiv.Configuration.Provider.RegisterSettings(e, this);
        }
    }
}
