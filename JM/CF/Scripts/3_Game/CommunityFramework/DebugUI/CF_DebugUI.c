class CF_DebugUI
{
	static ref CF_DebugUI_Type s_Types;

	private static int s_Count = 0;
	private static ref CF_DebugUI_Instance s_Instances[256];

	[CF_EventSubscriber(CF_DebugUI._Init, CF_LifecycleEvents.OnGameCreate)]
	static void _Init()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(null, "CF_DebugUI::_Init");
		#endif

		s_Types = new CF_DebugUI_Type();
		s_Count = 0;
	}

	[CF_EventSubscriber(CF_DebugUI._Cleanup, CF_LifecycleEvents.OnGameDestroy)]
	static void _Cleanup()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(null, "CF_DebugUI::_Cleanup");
		#endif

		s_Types = null;
		s_Count = 0;
	}

	static void Show(Class cls)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(null, "CF_DebugUI::Show", "" + cls);
		#endif

		if (s_Count >= 256) return;

		for (int i = 0; i < s_Count; i++)
		{
			if (s_Instances[i].GetClass() == cls) return;
		}

		s_Instances[s_Count] = new CF_DebugUI_Instance(cls);
		s_Count++;
	}

	static void Hide(Class cls)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(null, "CF_DebugUI::Hide", "" + cls);
		#endif

		for (int i = 0; i < s_Count; i++)
		{
			if (s_Instances[i].GetClass() == cls)
			{
				s_Count--;
				delete s_Instances[i];
				s_Instances[i] = s_Instances[s_Count];
				s_Instances[s_Count] = null;
			}
		}
	}
};
