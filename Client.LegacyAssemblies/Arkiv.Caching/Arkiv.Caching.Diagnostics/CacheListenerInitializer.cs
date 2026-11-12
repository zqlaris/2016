using System;
using Arkiv.Caching.Interfaces;
using Arkiv.Caching.MemCached;
using Arkiv.Configuration;

namespace Arkiv.Caching.Diagnostics
{
	public class CacheListenerInitializer
	{
		private bool _IsRegistered;

		private readonly object _Lock = new object();

		private readonly IArkivCacheListener _CacheListener;

		private readonly ISingleSetting<bool> _IsListeningSetting;

		private readonly MemcachedCache _MemcachedCache;

		public CacheListenerInitializer(ISingleSetting<bool> isListeningSetting, IArkivCacheListener cacheListener)
		{
			if (cacheListener == null)
			{
				throw new ArgumentNullException("cacheListener");
			}
			_CacheListener = cacheListener;
			if (isListeningSetting == null)
			{
				throw new ArgumentNullException("isListeningSetting");
			}
			_IsListeningSetting = isListeningSetting;
			_MemcachedCache = MemcachedCache.GetInstance();
			isListeningSetting.PropertyChanged += delegate
			{
				HandleListenerRegistration();
			};
			HandleListenerRegistration();
		}

		private void HandleListenerRegistration()
		{
			lock (_Lock)
			{
				bool value = _IsListeningSetting.Value;
				if (value && !_IsRegistered)
				{
					_IsRegistered = true;
					_MemcachedCache.AddArkivCacheListener(_CacheListener);
				}
				else if (!value && _IsRegistered)
				{
					_IsRegistered = false;
					_MemcachedCache.RemoveArkivCacheListener(_CacheListener);
				}
			}
		}
	}
}
