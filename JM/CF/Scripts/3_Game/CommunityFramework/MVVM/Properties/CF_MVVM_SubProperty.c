class CF_MVVM_SubProperty : CF_MVVM_Property
{
	protected CF_ModelBase m_SubModel;

	void CF_MVVM_SubProperty(CF_MVVM_View handler, string name)
	{
		CF_Trace trace(this, "CF_MVVM_SubProperty", "" + handler);
	}

	void SetSubModel(CF_ModelBase subModel)
	{
		CF_Trace trace(this, "SetSubModel", "" + subModel);

		m_SubModel = subModel;
	}

	override void OnView(CF_ModelBase model, /*notnull*/ CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView", "" + model, evt.String());

		g_Script.CallFunctionParams(m_SubModel, m_FunctionOnView, null, new Param2<CF_ModelBase, CF_EventArgs>(model, evt));
	}

	override void OnModel(CF_ModelBase model, /*notnull*/ CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel", "" + model, evt.String());

		g_Script.CallFunctionParams(m_SubModel, m_FunctionOnModel, null, new Param2<CF_ModelBase, CF_EventArgs>(model, evt));
	}
};