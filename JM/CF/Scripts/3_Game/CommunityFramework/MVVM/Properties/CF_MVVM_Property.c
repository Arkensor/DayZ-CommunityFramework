class CF_MVVM_Property
{
	private CF_MVVM_View m_Handler;

	private string m_Name;
	private string m_FunctionOnView;
	private string m_FunctionOnModel;

	private typename m_Type;
	private string m_VariableName;

	void CF_MVVM_Property(CF_MVVM_View handler, string name, string onView = "", string onModel = "")
	{
		CF_Trace trace(this, "CF_MVVM_Property", "" + handler, onView, onModel);

		m_Handler = handler;
		m_Name = name;

		m_FunctionOnView = "OnView_" + m_Name;
		m_FunctionOnModel = "OnModel_" + m_Name;

		if (onView != string.Empty)
			m_FunctionOnView = onView;
		if (onModel != string.Empty)
			m_FunctionOnModel = onModel;
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

		if (m_Type.IsInherited(Widget))
		{
			Widget widget = view.GetWidget().FindAnyWidget(m_VariableName);
			if (!widget) return;

			if (!widget.IsInherited(m_Type))
			{
				CF.Log.Error("Widget '%1' was not of type '%2' in model '%3'.", "" + _collection, "" + widget.ClassName(), "" + model);
				return;
			}

			EnScript.SetClassVar(model, m_VariableName, 0, widget);
			return;
		}
	}
	
	void OnView(CF_ModelBase model, /*notnull*/ CF_Event evt)
	{
		CF_Trace trace(this, "OnView", "" + model, evt.String());

		g_Script.CallFunctionParams(m_Handler, m_FunctionOnView, null, new Param2<CF_ModelBase, CF_Event>(model, evt));
	}

	void OnModel(CF_ModelBase model, /*notnull*/ CF_Event evt)
	{
		CF_Trace trace(this, "OnModel", "" + model, evt.String());

		g_Script.CallFunctionParams(m_Handler, m_FunctionOnModel, null, new Param2<CF_ModelBase, CF_Event>(model, evt));
	}
};