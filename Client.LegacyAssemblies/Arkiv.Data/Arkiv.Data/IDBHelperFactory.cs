namespace Arkiv.Data
{
	public interface IDBHelperFactory
	{
		DbHelper GetDBHelper(string connectionString);
	}
}
