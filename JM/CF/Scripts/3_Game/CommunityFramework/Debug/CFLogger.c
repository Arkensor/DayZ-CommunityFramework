class CFLogger
{
	[NonSerialized()]
	static ref ScriptInvoker OnUpdate = new ScriptInvoker;

	[NonSerialized()]
	protected string m_FileName;

	bool EnableDebug;

	autoptr map< string, bool > Modes = new ref map< string, bool >;
	
	void CFLogger()
	{
	}

	void Copy( CFLogger cpy )
	{
	}

	bool IsOn( string type )
	{
		return false;
	}

	void Log( string text, string type )
	{
	}
	
	void Err( string text, string type, bool stackTrce = true )
	{
	}

	void Save()
	{
	}
	
	void Defaults()
	{
	}
	
	void Send( PlayerIdentity sendTo )
	{
	}
	
	void Update()
	{
	}
}

static ref CFLogger GetLogger()
{
	return new CFLogger;
}
