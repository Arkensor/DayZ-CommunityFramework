class CF_DebugUI
{
	CF_DebugUI_Type Types;

	private ref set<Class> m_Classes = new set<Class>();

	void Show(Class cls)
	{
		m_Classes.Insert(cls);
	}

	void Hide(Class cls)
	{
		int idx = m_Classes.Find(cls);
		if (idx != -1) m_Classes.Remove(idx);
	}

	void Update(inout array<ref CF_DebugUI_Instance> instances)
	{
		instances.Clear();
		for (int i = 0; i < m_Classes.Count(); i++)
		{
			CF_DebugUI_Instance instance = new CF_DebugUI_Instance();
			instance.Add(m_Classes[i]);
			instances.Insert(instance);
		}
	}
};