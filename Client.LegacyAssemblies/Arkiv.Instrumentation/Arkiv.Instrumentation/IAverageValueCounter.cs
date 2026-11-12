namespace Arkiv.Instrumentation
{
	public interface IAverageValueCounter
	{
		void Sample(double value);
	}
}
