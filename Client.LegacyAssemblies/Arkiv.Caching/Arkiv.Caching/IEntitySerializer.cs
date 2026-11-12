using System;
using System.Runtime.CompilerServices;
using Arkiv.Caching.Interfaces;
using Arkiv.Caching.Shared;

namespace Arkiv.Caching
{
	internal interface IEntitySerializer
	{
		byte[] Serialize<TEntity>(TEntity entity) where TEntity : ICacheableObject;

		[return: TupleElementNames(new string[] { "Success", "Entity" })]
		ValueTuple<bool, TEntity> TryDeserializeFromRemoteCache<TEntity>(ISharedCacheClient sharedCacheClient, byte[] value, string key) where TEntity : ICacheableObject;
	}
}
