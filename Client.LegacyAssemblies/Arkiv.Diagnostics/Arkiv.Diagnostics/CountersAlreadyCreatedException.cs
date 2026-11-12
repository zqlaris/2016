using System;

namespace Arkiv.Diagnostics
{
	internal class CountersAlreadyCreatedException : Exception
	{
		public CountersAlreadyCreatedException(string message)
			: base(message)
		{
		}
	}
}
