using System;

namespace Arkiv.Configuration
{
	public interface IConnectionString
	{
		int Id { get; }

		string GroupName { get; }

		string Name { get; }

		string Value { get; }

		DateTime Updated { get; }
	}
}
