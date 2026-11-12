using System.Collections.Generic;

namespace Arkiv.Instrumentation.LegacySupport
{
	public interface ISimpleCounterCategoryFactory
	{
		ISimpleCounterCategory CreateSimpleCounterCategory(string categoryName, ICollection<string> counterNames);
	}
}
