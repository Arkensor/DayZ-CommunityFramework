class CF_ObservableCollection : CF_Collection
{
	private int m_LinkCount;
	private ref Param2<CF_ModelBase, string> m_Links[16];

	void Init(CF_ModelBase model, string prop)
	{
#ifdef COMPONENT_SYSTEM
		CF_MVVM._CheckInit();
#endif

#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_2(this, "Init").Add(model).Add(prop);
#endif

		m_Links[m_LinkCount] = new Param2<CF_ModelBase, string>(model, prop);
		m_LinkCount++;
	}

	void NotifyCollectionChanged(CF_CollectionEventArgs args)
	{
#ifdef CF_MVVM_TRACE
		auto trace = CF_Trace_1(this, "NotifyCollectionChanged").Add(args.GetDebugName());
#endif

		for (int i = 0; i < m_LinkCount; i++)
		{
			CF_MVVM.NotifyPropertyChanged(m_Links[i].param1, m_Links[i].param2, args);
		}
	}

	void Clear()
	{
	}

	void SetInt(int index, int value)
	{
		Param params = new Param2<int, int>(index, value);
		g_Script.CallFunctionParams(this, "Set", null, params);
	}

	void InsertInt(int value)
	{
		g_Script.CallFunction(this, "Insert", null, value);
	}

	int GetInt(int index)
	{
		return GetConverter(index).GetInt();
	}

	void SetBool(int index, bool value)
	{
		Param params = new Param2<int, bool>(index, value);
		g_Script.CallFunctionParams(this, "Set", null, params);
	}

	void InsertBool(bool value)
	{
		g_Script.CallFunction(this, "Insert", null, value);
	}

	bool GetBool(int index)
	{
		return GetConverter(index).GetBool();
	}

	void SetFloat(int index, float value)
	{
		Param params = new Param2<int, float>(index, value);
		g_Script.CallFunctionParams(this, "Set", null, params);
	}

	void InsertFloat(float value)
	{
		g_Script.CallFunction(this, "Insert", null, value);
	}

	float GetFloat(int index)
	{
		return GetConverter(index).GetFloat();
	}

	void SetVector(int index, vector value)
	{
		Param params = new Param2<int, vector>(index, value);
		g_Script.CallFunctionParams(this, "Set", null, params);
	}

	void InsertVector(vector value)
	{
		g_Script.CallFunction(this, "Insert", null, value);
	}

	vector GetVector(int index)
	{
		return GetConverter(index).GetVector();
	}

	void SetString(int index, string value)
	{
		Param params = new Param2<int, string>(index, value);
		g_Script.CallFunctionParams(this, "Set", null, params);
	}

	void InsertString(string value)
	{
		g_Script.CallFunction(this, "Insert", null, value);
	}

	string GetString(int index)
	{
		return GetConverter(index).GetString();
	}

	void SetClass(int index, Class value)
	{
		Param params = new Param2<int, Class>(index, value);
		g_Script.CallFunctionParams(this, "Set", null, params);
	}

	void InsertClass(Class value)
	{
		g_Script.CallFunction(this, "Insert", null, value);
	}

	Class GetClass(int index)
	{
		return GetConverter(index).GetClass();
	}

	void SetManaged(int index, Managed value)
	{
		Param params = new Param2<int, Managed>(index, value);
		g_Script.CallFunctionParams(this, "Set", null, params);
	}

	void InsertManaged(Managed value)
	{
		g_Script.CallFunction(this, "Insert", null, value);
	}

	Managed GetManaged(int index)
	{
		return GetConverter(index).GetManaged();
	}
};
