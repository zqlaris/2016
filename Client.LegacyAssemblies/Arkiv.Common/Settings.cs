namespace Arkiv.Common.Properties
{
    [System.Configuration.SettingsProvider(typeof(Arkiv.Configuration.Provider))]
    public sealed partial class Settings
    {
        protected override void OnSettingsLoaded(object sender, System.Configuration.SettingsLoadedEventArgs e)
        {
            base.OnSettingsLoaded(sender, e);
            global::Arkiv.Configuration.Provider.RegisterSettings(e, this);
        }
    }
}
