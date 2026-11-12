using System.Runtime.InteropServices;

namespace ArkivLib
{
	[ComImport]
	[Guid("794D78C9-B0EC-4BC9-B881-B5F45E1D530B")]
	[CoClass(typeof(WorkspaceClass))]
	public interface Workspace : IWorkspace
	{
	}
}
