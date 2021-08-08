class CF_DebugUI : Managed
{
	static ref CF_DebugUI_Type s_Types;

	private static bool s_Allowed = false;

	private static ref map<Class, CF_DebugUI_Instance> s_Instances;

	[CF_EventSubscriber(CF_DebugUI._Init, CF_LifecycleEvents.OnGameCreate)]
	static void _Init()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(null, "CF_DebugUI::_Init");
		#endif

		s_Types = new CF_DebugUI_Type();
		s_Instances = new map<Class, CF_DebugUI_Instance>();

		SetAllowed(false);
	}

	[CF_EventSubscriber(CF_DebugUI._Cleanup, CF_LifecycleEvents.OnGameDestroy)]
	static void _Cleanup()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(null, "CF_DebugUI::_Cleanup");
		#endif

		s_Types = null;
		s_Instances = null;
	}

	[CF_EventSubscriber(CF_DebugUI._MissionCleanup, CF_LifecycleEvents.OnMissionDestroy)]
	static void _MissionCleanup()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(null, "CF_DebugUI::_MissionCleanup");
		#endif

		SetAllowed(false);
	}

	static bool IsAllowed()
	{
		return s_Allowed;
	}

	static void SetAllowed(bool newState)
	{
		s_Allowed = newState;
	}

	static void Create(Class instance, string title = "##")
	{
		#ifdef SERVER
		return null;
		#endif

		if (!s_Allowed || !instance) return;

		CF_DebugUI_Instance cf_debug;
		s_Instances.Find(instance, cf_debug);

		bool overrideTitle = title == "##";

		if (overrideTitle && !cf_debug)
		{
			string hex = "" + instance;
			int previousIndex = hex.IndexOf("<");
			int index = -1;
			while (previousIndex != -1)
			{
				index = previousIndex;
				hex = hex.Substring(index + 1, hex.Length() - index - 1);
				previousIndex = hex.IndexOf("<");
			}
			hex = hex.Substring(0, hex.Length() - 1);

			title = instance.ClassName();
		
			Object object;
			if (Class.CastTo(object, instance))
			{
				title = object.GetDisplayName();

				if (GetGame().IsMultiplayer())
				{
					title += " (" + object.GetNetworkIDString() + ")";
				}
			}

			title += " (" + hex + ")";
		}

		if (cf_debug)
		{
			if (!overrideTitle)
			{
				cf_debug.SetTitle(title);
			}

			return;
		}

		cf_debug = new CF_DebugUI_Instance(instance, title);
		s_Instances.Insert(instance, cf_debug);
	}

	static void Destroy(Class instance)
	{
		s_Instances.Remove(instance);
	}
};
