namespace Arkiv.Instrumentation
{
	public interface IMaximumValueCounter
	{
		void Sample(double value);
	}
}
