class CF_ModStorage_Data
{
	protected string m_VariableName;

	void Write(ParamsWriteContext ctx)
	{
	}

	void Read(ParamsReadContext ctx)
	{
	}

	void OnSet()
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

	void SetFrom(Class cls, string name, int idx = 0);
	void SetTo(Class cls, string name, int idx = 0);

	Param Get()
	{
		return NULL;
	}

	bool Get(inout Class cls)
	{
		return false;
	}
};