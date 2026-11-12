using System.Collections.Generic;

namespace Arkiv.Diagnostics
{
	public class SimpleCounterCategoryFactory : ISimpleCounterCategoryFactory
	{
		public ISimpleCounterCategory CreateSimplePerfmonCounterCategory(string categoryName, ICollection<string> counterNames)
		{
			return new SimplePerfmonCounterCategory(categoryName, counterNames);
		}
	}
}
