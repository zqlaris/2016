using System.Text;
using Arkiv.Hashing;

namespace Arkiv.Common
{
	public static class Counters
	{
		private static readonly string _DefaultKey = "Arkiv.Platform.Common.Counter";

		public static int GetStableRolloutPercentage(long userid, string key)
		{
			if (string.IsNullOrEmpty(key))
			{
				key = _DefaultKey;
			}
			string input = userid + key;
			return (int)(MurmurHash2.Hash(Encoding.ASCII.GetBytes(input)) % 100);
		}
	}
}
