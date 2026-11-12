namespace Arkiv
{
	public interface IParallelWorkTask
	{
		string UniqueId { get; }

		void ProcessTaskAndMarkComplete();
	}
}
