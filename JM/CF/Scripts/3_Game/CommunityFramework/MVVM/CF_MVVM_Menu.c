class CF_MVVM_Menu : UIScriptedMenu
{
	private CF_MVVM_Linker m_Linker;

	private ref CF_ModelBase m_Model;

	override Widget Init()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "Init");
#endif

		layoutRoot = GetGame().GetWorkspace().CreateWidget(FrameWidgetTypeID, 0, 0, 1, 1, WidgetFlags.VISIBLE, 0, 0, null);
		return layoutRoot;
	}

	void SetModel(CF_ModelBase model, string layoutFile)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_2(this, "SetModel").Add(model).Add(layoutFile);
#endif

		m_Model = model;

		m_Linker = CF_MVVM.Create(m_Model, layoutFile, layoutRoot);
		m_Linker.OnDestroy.AddSubscriber(RemoveModel);
	}

	void RemoveModel()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "RemoveModel");
#endif

		m_Linker.OnDestroy.RemoveSubscriber(RemoveModel);

		Close();
	}
};
