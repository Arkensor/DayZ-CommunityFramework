class CF_MVVM_WidgetProperty : CF_MVVM_Property
{
	void CF_MVVM_WidgetProperty(CF_MVVM_View handler, string name)
	{
		CF_Trace trace(this, "CF_MVVM_WidgetProperty", "" + handler);
	}

	override void Assign(CF_ModelBase model, CF_MVVM_View view)
	{
		CF_Trace trace(this, "Assign", "" + model, "" + view);

		Widget widget = view.GetWidget().FindAnyWidget(m_VariableName);
		if (!widget) return;

		if (!widget.IsInherited(m_Type))
		{
			CF.Log.Error("Widget '%1' was not of type '%2' in model '%3'.", "" + widget.ClassName(), m_Type.ToString(), "" + model);
			return;
		}

		EnScript.SetClassVar(model, m_VariableName, 0, widget);
	}

	override void OnView(CF_ModelBase model, /*notnull*/ CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView", "" + model, evt.String());
	}

	override void OnModel(CF_ModelBase model, /*notnull*/ CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel", "" + model, evt.String());
	}
};