using System;

namespace Arkiv.Common
{
	public class OperationUnavailableException : Exception
	{
		public OperationUnavailableException()
		{
		}

		public OperationUnavailableException(string message)
			: base(message)
		{
		}

		public OperationUnavailableException(string message, Exception innerException)
			: base(message, innerException)
		{
		}
	}
}
