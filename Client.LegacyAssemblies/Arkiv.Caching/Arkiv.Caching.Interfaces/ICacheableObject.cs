using System.Collections.Generic;

namespace Arkiv.Caching.Interfaces
{
	public interface ICacheableObject
	{
		CacheInfo CacheInfo { get; }

		IEnumerable<string> BuildEntityIDLookups();

		IEnumerable<StateToken> BuildStateTokenCollection();
	}
	public interface ICacheableObject<TIndex> : ICacheableObject
	{
		TIndex ID { get; }
	}
}
