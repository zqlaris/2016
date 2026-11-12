using System;
using System.Collections.Generic;
using StackExchange.Redis;

namespace Arkiv.Redis
{
	public delegate ValueTuple<IEnumerable<string>, IEnumerable<TResult>> DatabaseMultiActionWithKeys<TResult>(IDatabase database, IReadOnlyCollection<string> partitionKeys);
}
