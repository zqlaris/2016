using System.Threading.Tasks;
using StackExchange.Redis;

namespace Arkiv.Redis
{
	public interface IConnectionBuilder
	{
		Task<IConnectionMultiplexer> CreateConnectionMultiplexerAsync(ConfigurationOptions configuration);
	}
}
