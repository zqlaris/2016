using System;

namespace Arkiv.Configuration
{
	public class WeightedCsvParseException : Exception
	{
		public WeightedCsvParseException(string message)
			: base(message)
		{
		}
	}
}
