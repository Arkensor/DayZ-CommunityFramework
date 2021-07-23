class CF_MVVM_SubProperty : CF_MVVM_Property
{
	protected CF_ModelBase m_SubModel;

	void CF_MVVM_SubProperty(CF_ViewModel handler, string name)
	{
		CF_Trace trace(this, "CF_MVVM_SubProperty", "" + handler);
	}

	void SetSubModel(CF_ModelBase subModel)
	{
		CF_Trace trace(this, "SetSubModel", "" + subModel);

		m_SubModel = subModel;
	}

	override void OnView(/*notnull*/ CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnView", evt.ToStr());

		g_Script.CallFunctionParams(m_SubModel, m_FunctionOnView, null, new Param2<CF_ModelBase, CF_EventArgs>(m_Model, evt));
	}

	override void OnModel(/*notnull*/ CF_EventArgs evt)
	{
		CF_Trace trace(this, "OnModel", evt.ToStr());

		g_Script.CallFunctionParams(m_SubModel, m_FunctionOnModel, null, new Param2<CF_ModelBase, CF_EventArgs>(m_Model, evt));
	}
};