using System.Collections.Generic;

namespace Arkiv.Hashing
{
	public interface IPartitionedKeyGenerator
	{
		string GetPartitionKey(string keyToBePartitioned);

		IReadOnlyCollection<string> GetAllPartitionKeys();
	}
}
