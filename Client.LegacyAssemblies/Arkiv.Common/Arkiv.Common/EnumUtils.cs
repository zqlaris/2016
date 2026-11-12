using Arkiv.Common.NetStandard;

namespace Arkiv.Common
{
	public static class EnumUtils
	{
		public static TEnum? StrictTryParseEnum<TEnum>(string value) where TEnum : struct
		{
			return EnumUtils.StrictTryParseEnum<TEnum>(value);
		}
	}
}
