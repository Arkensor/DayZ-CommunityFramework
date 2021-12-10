class CF_MVVM_SubProperty : CF_MVVM_Property
{
	protected CF_ModelBase m_SubModel;

	void CF_MVVM_SubProperty(CF_ViewModel handler, string name)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "CF_MVVM_SubProperty").Add(handler).Add(name);
#endif
	}

	void SetSubModel(CF_ModelBase subModel)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "SetSubModel").Add(subModel);
#endif

		m_SubModel = subModel;
	}

	override void OnView(/*notnull*/ CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnView").Add(args);
#endif

		g_Script.CallFunctionParams(m_SubModel, "OnView_" + m_Name, null, new Param2<CF_ModelBase, CF_EventArgs>(m_Model, args));
	}

	override void OnModel(/*notnull*/ CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_1(this, "OnModel").Add(args);
#endif

		g_Script.CallFunctionParams(m_SubModel, "OnModel_" + m_Name, null, new Param2<CF_ModelBase, CF_EventArgs>(m_Model, args));
	}
};