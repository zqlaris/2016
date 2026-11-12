using System;

namespace Arkiv.Instrumentation.LegacySupport
{
	internal class NoCountersSpecifiedForCategoryException : Exception
	{
		public NoCountersSpecifiedForCategoryException(string categoryName)
			: base(categoryName)
		{
		}
	}
}
