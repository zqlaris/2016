namespace Arkiv.Instrumentation
{
	public interface IPercentileCounter
	{
		void Sample(double value);
	}
}
