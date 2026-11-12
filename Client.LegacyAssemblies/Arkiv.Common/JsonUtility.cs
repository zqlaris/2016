using System.Text;
using System.Web.Script.Serialization;

namespace Arkiv.Common
{
    public abstract class Json
    {
        public virtual string Serialize()
        {
            if (SerializedData == null)
            {
                var value = new JavaScriptSerializer().Serialize(this);
                SerializedData = value.Convert(Encoding.Unicode, Encoding.UTF8);
            }

            return SerializedData;
        }

        protected string SerializedData;
    }
}
