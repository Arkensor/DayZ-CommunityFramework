class CF_MVVM_WidgetProperty : CF_MVVM_Property
{
	void CF_MVVM_WidgetProperty(CF_ViewModel handler, string name)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "CF_MVVM_WidgetProperty", "" + handler);
		#endif

		SetVariableName(name);
	}

	override void Link(CF_ModelBase model, typename variableType, CF_TypeConverter typeConverter)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Assign", "" + model);
		#endif

		Widget widget = m_ViewModel.GetWidget().FindAnyWidget(m_VariableName);
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
		CF_Trace trace(this, "OnView", evt.ToStr());
		#endif
	}

	override void OnModel(/*notnull*/ CF_EventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel", evt.ToStr());
		#endif
	}
};