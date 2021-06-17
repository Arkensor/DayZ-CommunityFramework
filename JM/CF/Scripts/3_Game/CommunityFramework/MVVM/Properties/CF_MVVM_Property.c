class CF_MVVM_Property
{
	private CF_MVVM_View m_Handler;

	private string m_FunctionOnView;
	private string m_FunctionOnModel;

	void CF_MVVM_Property(CF_MVVM_View handler, string onView, string onModel)
	{
		CF_Trace trace(this, "CF_MVVM_Property", "" + handler, onView, onModel);

		m_Handler = handler;
		m_FunctionOnView = onView;
		m_FunctionOnModel = onModel;
	}
	
	void OnView(CF_Model_Base model)
	{
		CF_Trace trace(this, "OnView", "" + model);

		g_Script.CallFunction(m_Handler, m_FunctionOnView, null, model);
	}

	void OnModel(CF_Model_Base model)
	{
		CF_Trace trace(this, "OnModel", "" + model);

		g_Script.CallFunction(m_Handler, m_FunctionOnModel, null, model);
	}
};