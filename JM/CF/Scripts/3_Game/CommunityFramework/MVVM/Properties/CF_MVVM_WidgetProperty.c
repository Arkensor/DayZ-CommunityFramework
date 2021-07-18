class CF_MVVM_WidgetProperty : CF_MVVM_Property
{
	void CF_MVVM_WidgetProperty(CF_MVVM_View handler, string name)
	{
		CF_Trace trace(this, "CF_MVVM_WidgetProperty", "" + handler);
	}

	override void Link(CF_ModelBase model)
	{
		CF_Trace trace(this, "Assign", "" + model);

		Widget widget = m_ViewModel.GetWidget().FindAnyWidget(m_VariableName);
		if (!widget) return;

		if (!widget.IsInherited(m_Type))
		{
			CF.Log.Error("Widget '%1' was not of type '%2' in model '%3'.", "" + widget.ClassName(), m_Type.ToString(), "" + model);
			return;
		}

		EnScript.SetClassVar(model, m_VariableName, 0, widget);
	}

	override void OnView(/*notnull*/ CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView", evt.ToStr());
	}

	override void OnModel(/*notnull*/ CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel", evt.ToStr());
	}
};