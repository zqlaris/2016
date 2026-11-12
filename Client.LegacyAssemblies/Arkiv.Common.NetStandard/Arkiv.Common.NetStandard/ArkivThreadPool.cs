using System;
using System.Threading;
using Arkiv.EventLog;

namespace Arkiv.Common.NetStandard
{
	public static class ArkivThreadPool
	{
		private static int _QueueLength;

		public static int QueueLength
		{
			get
			{
				return _QueueLength;
			}
		}

		public static bool QueueUserWorkItem(Action callback)
		{
			Interlocked.Increment(ref _QueueLength);
			return ThreadPool.QueueUserWorkItem(delegate
			{
				try
				{
					callback();
				}
				catch (ThreadAbortException)
				{
					throw;
				}
				catch (Exception ex2)
				{
					StaticLoggerRegistry.Instance.Error(ex2);
				}
				finally
				{
					Interlocked.Decrement(ref _QueueLength);
				}
			});
		}

		public static void GetAvailableThreads(out int workerThreads, out int completionPortThreads)
		{
			ThreadPool.GetAvailableThreads(out workerThreads, out completionPortThreads);
		}
	}
}
