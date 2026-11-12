namespace Arkiv.Platform.Infrastructure
{
	public static class ServerValidator
	{
		public static readonly IServerValidator ArkivServerValidator = new ServerValidatorInstance();
	}
}
