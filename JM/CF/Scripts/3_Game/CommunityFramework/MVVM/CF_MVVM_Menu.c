class CF_MVVM_Menu : UIScriptedMenu
{
	private CF_MVVM_Linker m_Linker;

	private ref CF_ModelBase m_Model;

	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidget(FrameWidgetTypeID, 0, 0, 1, 1, WidgetFlags.VISIBLE, 0, 0, null);
		return layoutRoot;
	}

	void SetModel(CF_ModelBase model, string layoutFile)
	{
		m_Model = model;

		m_Linker = CF_MVVM.Create(m_Model, layoutFile, layoutRoot);
		m_Linker.OnDestroy.AddSubscriber(RemoveModel);
	}

	void RemoveModel()
	{
		m_Linker.OnDestroy.RemoveSubscriber(RemoveModel);

		Close();
	}
};
