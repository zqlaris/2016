using System;
using Arkiv.Common.NetStandard;

namespace Arkiv
{
	public static class ArkivThreadPool
	{
		public static int QueueLength
		{
			get
			{
				return Arkiv.Common.NetStandard.ArkivThreadPool.QueueLength;
			}
		}

		public static bool QueueUserWorkItem(Action callback)
		{
			return Arkiv.Common.NetStandard.ArkivThreadPool.QueueUserWorkItem(callback);
		}

		public static void GetAvailableThreads(out int workerThreads, out int completionPortThreads)
		{
			Arkiv.Common.NetStandard.ArkivThreadPool.GetAvailableThreads(out workerThreads, out completionPortThreads);
		}
	}
}
