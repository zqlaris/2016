using System.Web;

namespace Arkiv.Common
{
	public class TextTransforms
	{
		public static string transformString(string stringToTransform) => performCarriageReturnSubstitution(HttpContext.Current.Server.HtmlEncode(stringToTransform));
		public static string performCarriageReturnSubstitution(string text) => text.Replace("\n", "<br />");
	}
}
