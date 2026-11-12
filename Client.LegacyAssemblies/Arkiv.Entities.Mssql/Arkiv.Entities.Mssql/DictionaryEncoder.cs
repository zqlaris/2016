using System.Collections.Generic;

namespace Arkiv.Entities.Mssql
{
	public static class DictionaryEncoder
	{
		public static T Decode<T>(IDictionary<string, object> record) where T : class, new()
		{
			return DictionaryDeserializerCache<T>.Default.Deserialize(record);
		}
	}
}
