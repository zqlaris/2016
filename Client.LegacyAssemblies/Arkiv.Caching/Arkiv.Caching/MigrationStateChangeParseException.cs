using System;

namespace Arkiv.Caching
{
	internal class MigrationStateChangeParseException : Exception
	{
		public MigrationStateChangeParseException(string message)
			: base(message)
		{
		}
	}
}
