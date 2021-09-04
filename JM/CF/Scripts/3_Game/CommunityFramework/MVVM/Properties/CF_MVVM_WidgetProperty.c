class CF_MVVM_WidgetProperty : CF_MVVM_Property
{
	void CF_MVVM_WidgetProperty(CF_ViewModel handler, string name)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "CF_MVVM_WidgetProperty").Add(handler);
		#endif

		SetVariableName(name);
	}

	override void Link(CF_ModelBase model, typename variableType, CF_TypeConverter typeConverter)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "Assign").Add(model);
		#endif

		Widget widget = m_ViewModel.GetWidget();
		if (widget && widget.GetName() != m_VariableName) widget = widget.FindAnyWidget(m_VariableName);
		if (!widget) return;

		if (!widget.IsInherited(variableType))
		{
			CF_Log.Error("Widget '%1' was not of type '%2' in model '%3'.", "" + widget.ClassName(), variableType.ToString(), "" + model);
			return;
		}

		EnScript.SetClassVar(model, m_VariableName, 0, widget);
	}

	override void OnView(/*notnull*/ CF_EventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnView").Add(evt.ToStr());
		#endif
	}

	override void OnModel(/*notnull*/ CF_EventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnModel").Add(evt.ToStr());
		#endif
	}
};