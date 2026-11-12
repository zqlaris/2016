using System;

namespace Arkiv.Diagnostics
{
	internal class NoCountersSpecifiedForCategoryException : Exception
	{
		public NoCountersSpecifiedForCategoryException(string categoryName)
			: base(categoryName)
		{
		}
	}
}
