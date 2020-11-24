class CF_ModStorage_Data
{
	protected string m_VariableName;

	void Write( ParamsWriteContext ctx )
	{
	}

	void Read( ParamsReadContext ctx )
	{
	}
	
	bool IsNull()
	{
		return false;
	}
	
	void SetVariableName(string name)
	{
		m_VariableName = name;
	}
	
	string GetVariableName()
	{
		return m_VariableName;
	}
	
	typename GetType();

	Param Get()
	{
		return NULL;
	}

	bool Get(out Class cls)
	{
		return false;
	}
};