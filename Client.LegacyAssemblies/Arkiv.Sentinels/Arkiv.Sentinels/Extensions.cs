using System;

namespace Arkiv.Sentinels
{
	internal static class Extensions
	{
		internal static void CheckAndDispose(this IDisposable disposable)
		{
			if (disposable != null)
			{
				disposable.Dispose();
			}
		}
	}
}
