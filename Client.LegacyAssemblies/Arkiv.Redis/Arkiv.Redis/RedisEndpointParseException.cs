using System;

namespace Arkiv.Redis
{
	internal class RedisEndpointParseException : Exception
	{
		public RedisEndpointParseException(string message)
			: base(message)
		{
		}
	}
}
