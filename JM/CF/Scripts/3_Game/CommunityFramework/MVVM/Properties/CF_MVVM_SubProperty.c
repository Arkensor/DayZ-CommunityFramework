class CF_MVVM_SubProperty : CF_MVVM_Property
{
	protected CF_ModelBase m_SubModel;

	void CF_MVVM_SubProperty(CF_ViewModel handler, string name)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "CF_MVVM_SubProperty", "" + handler);
		#endif
	}

	void SetSubModel(CF_ModelBase subModel)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "SetSubModel", "" + subModel);
		#endif

		m_SubModel = subModel;
	}

	override void OnView(/*notnull*/ CF_EventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnView", evt.ToStr());
		#endif

		g_Script.CallFunctionParams(m_SubModel, "OnView_" + m_Name, null, new Param2<CF_ModelBase, CF_EventArgs>(m_Model, evt));
	}

	override void OnModel(/*notnull*/ CF_EventArgs evt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnModel", evt.ToStr());
		#endif

		g_Script.CallFunctionParams(m_SubModel, "OnModel_" + m_Name, null, new Param2<CF_ModelBase, CF_EventArgs>(m_Model, evt));
	}
};