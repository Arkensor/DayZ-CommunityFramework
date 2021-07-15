class CF_MVVM_Property
{
	protected CF_ModelBase m_Model;
	protected CF_MVVM_View m_ViewModel;

	protected string m_Name;
	protected string m_FunctionOnView;
	protected string m_FunctionOnModel;

	protected typename m_Type;
	protected string m_VariableName;

	void CF_MVVM_Property(CF_MVVM_View handler, string name)
	{
		CF_Trace trace(this, "CF_MVVM_Property", "" + handler, name);

		m_ViewModel = handler;
		m_Name = name;

		m_FunctionOnView = "OnView_" + m_Name;
		m_FunctionOnModel = "OnModel_" + m_Name;
	}

	void ~CF_MVVM_Property()
	{
		//TODO: remove from CF_MVVM properties map
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

	void Link(CF_ModelBase model)
	{
		CF_Trace trace(this, "Assign", "" + model);

		m_Model = model;

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

		CF_TypeConverter typeConverter = CF_MVVM.GetPropertyType(model, m_VariableName);
		if (!typeConverter)
		{
			CF.Log.Error("'%1.%2' has no assigned type converter!", "" + model, m_VariableName);
			return;
		}

		EnScript.SetClassVar(m_ViewModel, "_" + m_Name, 0, typeConverter);
	}
	
	void OnView(/*notnull*/ CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView", evt.String());

		g_Script.CallFunctionParams(m_ViewModel, m_FunctionOnView, null, new Param2<CF_ModelBase, CF_EventArgs>(m_Model, evt));
	}

	void OnModel(/*notnull*/ CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel", evt.String());

		g_Script.CallFunctionParams(m_ViewModel, m_FunctionOnModel, null, new Param2<CF_ModelBase, CF_EventArgs>(m_Model, evt));
	}
};