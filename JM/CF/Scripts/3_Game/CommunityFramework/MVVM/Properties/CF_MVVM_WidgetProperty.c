class CF_MVVM_WidgetProperty : CF_MVVM_Property
{
	void CF_MVVM_WidgetProperty(CF_MVVM_View handler, string name)
	{
		CF_Trace trace(this, "CF_MVVM_WidgetProperty", "" + handler);
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