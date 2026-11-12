using System.Threading;
using System.Threading.Tasks;

namespace Arkiv.Mssql
{
	public interface IDatabaseObserver
	{
		void Dispose();

		void Register();

		Task RegisterAsync(CancellationToken cancellationToken = default(CancellationToken));

		void Unregister();

		Task UnregisterAsync(CancellationToken cancellationToken = default(CancellationToken));
	}
}
