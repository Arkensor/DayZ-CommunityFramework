class CF_MVVM_Property
{
	protected CF_MVVM_View m_Handler;

	protected string m_Name;
	protected string m_FunctionOnView;
	protected string m_FunctionOnModel;

	protected typename m_Type;
	protected string m_VariableName;

	void CF_MVVM_Property(CF_MVVM_View handler, string name)
	{
		CF_Trace trace(this, "CF_MVVM_Property", "" + handler);

		m_Handler = handler;
		m_Name = name;

		m_FunctionOnView = "OnView_" + m_Name;
		m_FunctionOnModel = "OnModel_" + m_Name;
	}

	void SetVariableName(string variableName)
	{
		m_VariableName = variableName;
	}

	string GetVariableName()
	{
		return m_VariableName;
	}

	void SetType(typename type)
	{
		m_Type = type;
	}

	typename GetType()
	{
		return m_Type;
	}

	string GetName()
	{
		return m_Name;
	}

	void Assign(CF_ModelBase model, CF_MVVM_View view)
	{
		CF_Trace trace(this, "Assign", "" + model, "" + view);

		if (m_Type.IsInherited(CF_ObservableCollection))
		{
			CF_ObservableCollection _collection;
			EnScript.GetClassVar(model, m_VariableName, 0, _collection);
			if (!_collection)
			{
				CF.Log.Error("'%1' was null in model '%2'. Treat this variable as final, initiate during construction.", "" + _collection, "" + model);
				return;
			}

			_collection.Init(model, m_VariableName);
			return;
		}

		CF_TypeConverter typeConverter = CF.MVVM.GetPropertyType(model, m_VariableName);
		if (!typeConverter)
		{
			CF.Log.Error("'%1.%2' has no assigned type converter!", "" + model, m_VariableName);
			return;
		}

		EnScript.SetClassVar(view, "_" + m_Name, 0, typeConverter);
	}
	
	void OnView(CF_ModelBase model, /*notnull*/ CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView", "" + model, evt.String());

		g_Script.CallFunctionParams(m_Handler, m_FunctionOnView, null, new Param2<CF_ModelBase, CF_EventArgs>(model, evt));
	}

	void OnModel(CF_ModelBase model, /*notnull*/ CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel", "" + model, evt.String());

		g_Script.CallFunctionParams(m_Handler, m_FunctionOnModel, null, new Param2<CF_ModelBase, CF_EventArgs>(model, evt));
	}
};