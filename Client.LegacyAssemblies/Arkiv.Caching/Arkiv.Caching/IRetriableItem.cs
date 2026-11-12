namespace Arkiv.Caching
{
	internal interface IRetriableItem
	{
		int CurrentAttempt { get; set; }
	}
}
