using Arkiv.Caching.Interfaces;

namespace Arkiv.Data.Interfaces
{
	public interface IArkivEntity<TIndex, TDal> : ICacheableObject<TIndex>, ICacheableObject
	{
		void Construct(TDal dal);
	}
}
