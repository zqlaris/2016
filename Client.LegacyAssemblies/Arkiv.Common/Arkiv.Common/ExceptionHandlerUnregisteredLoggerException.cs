using System;

namespace Arkiv.Common
{
	public class ExceptionHandlerUnregisteredLoggerException : Exception
	{
		public ExceptionHandlerUnregisteredLoggerException(string message, Exception innerException)
			: base(message, innerException)
		{
		}
	}
}
