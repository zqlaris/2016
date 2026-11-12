using System.Collections.Generic;

namespace Arkiv.Diagnostics
{
	public interface ISimpleCounterCategoryFactory
	{
		ISimpleCounterCategory CreateSimplePerfmonCounterCategory(string categoryName, ICollection<string> counterNames);
	}
}
