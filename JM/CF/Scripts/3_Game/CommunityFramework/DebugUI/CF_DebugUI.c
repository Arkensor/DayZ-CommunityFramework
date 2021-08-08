class CF_DebugUI : Managed
{
	static ref CF_DebugUI_Type s_Types;

	private Class m_Owner;
	private ref CF_DebugUI_Instance m_Instance;

	[CF_EventSubscriber(CF_DebugUI._Init, CF_LifecycleEvents.OnGameCreate)]
	static void _Init()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(null, "CF_DebugUI::_Init");
		#endif

		s_Types = new CF_DebugUI_Type();
	}

	[CF_EventSubscriber(CF_DebugUI._Cleanup, CF_LifecycleEvents.OnGameDestroy)]
	static void _Cleanup()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(null, "CF_DebugUI::_Cleanup");
		#endif

		s_Types = null;
	}

	static CF_DebugUI Create(Class cls, string title = "##")
	{
		if (title == "##")
		{
			title = "Debug " + cls.ClassName() + "";
		
			Object obj;
			if (Class.CastTo(obj, cls))
			{
				title = "Debug " + obj.GetType() + "";
			}
		}

		CF_DebugUI instance;

		if (!instance)
		{
			instance = new CF_DebugUI();
			instance.m_Instance = new CF_DebugUI_Instance(cls, title);
			instance.m_Owner = cls;
		}

		return instance;
	}

	// Creation of DebugUI is done through the static Create. 
	// Jacob: static methods can't access protected functions.
	private void CF_DebugUI()
	{
	}

	void ~CF_DebugUI()
	{
		m_Instance.Destroy();
	}

	void Show()
	{
		m_Instance.Start();
	}

	void Close()
	{
		m_Instance.Stop();
	}
};
