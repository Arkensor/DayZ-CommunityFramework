class CF_DebugUI
{
	static ref CF_DebugUI_Type s_Types;

	private static ref set<Class> s_Classes;

	[CF_EventSubscriber(CF_DebugUI._Init, CF_LifecycleEvents.OnGameCreate)]
	static void _Init()
	{
		s_Types = new CF_DebugUI_Type();
		s_Classes = new set<Class>();
	}

	[CF_EventSubscriber(CF_DebugUI._Cleanup, CF_LifecycleEvents.OnGameDestroy)]
	static void _Cleanup()
	{
		s_Types = null;
		s_Classes = null;
	}

	static void Show(Class cls)
	{
		s_Classes.Insert(cls);
	}

	static void Hide(Class cls)
	{
		int idx = s_Classes.Find(cls);
		if (idx != -1) s_Classes.Remove(idx);
	}

	static void Update(inout array<ref CF_DebugUI_Instance> instances)
	{
		instances.Clear();
		for (int i = 0; i < s_Classes.Count(); i++)
		{
			CF_DebugUI_Instance instance = new CF_DebugUI_Instance();
			instance.Add(s_Classes[i]);
			instances.Insert(instance);
		}
	}
};
