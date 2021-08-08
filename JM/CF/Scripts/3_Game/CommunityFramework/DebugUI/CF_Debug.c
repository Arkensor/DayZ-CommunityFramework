class CF_Debug : CF_TimerBase
{
	static ref CF_DebugUI_Type s_Types;

	private static bool s_Allowed = false;

	private static ref map<Class, CF_Debug> s_Instances;

	[CF_EventSubscriber(CF_Debug._Init, CF_LifecycleEvents.OnGameCreate)]
	static void _Init()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(null, "CF_Debug::_Init");
		#endif

		s_Types = new CF_DebugUI_Type();
		s_Instances = new map<Class, CF_Debug>();

		SetAllowed(false);
	}

	[CF_EventSubscriber(CF_Debug._Cleanup, CF_LifecycleEvents.OnGameDestroy)]
	static void _Cleanup()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(null, "CF_Debug::_Cleanup");
		#endif

		s_Types = null;
		s_Instances = null;
	}

	[CF_EventSubscriber(CF_Debug._MissionCleanup, CF_LifecycleEvents.OnMissionDestroy)]
	static void _MissionCleanup()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(null, "CF_Debug::_MissionCleanup");
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

		CF_Debug cf_debug;
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
				cf_debug.SetName(title);
			}

			return;
		}

		cf_debug = new CF_Debug(instance, title);
		s_Instances.Insert(instance, cf_debug);
	}

	static void Destroy(Class instance)
	{
		s_Instances.Remove(instance);
	}

	protected ref array<ref CF_DebugOutput> m_Outputs = new array<ref CF_DebugOutput>();

	protected Class m_Instance;
	protected string m_Name;

	protected CF_DebugUI m_UI;

	/*private*/ void CF_Debug(Class instance, string name)
	{
		m_Instance = instance;
		m_Name = name;

		ShowWindow();
	}

	void SetName(string name)
	{
		m_Name = name;

		foreach (auto output : m_Outputs)
		{
			output.SetName(name);
		}
	}

	string GetName()
	{
		return m_Name;
	}

	void Add(string value)
	{
		foreach (auto output : m_Outputs)
		{
			output.Add(value);
		}
	}
	
	void Add(string name, int value)
	{
		foreach (auto output : m_Outputs)
		{
			output.Add(name, value);
		}
	}
	
	void Add(string name, bool value)
	{
		foreach (auto output : m_Outputs)
		{
			output.Add(name, value);
		}
	}
	
	void Add(string name, float value)
	{
		foreach (auto output : m_Outputs)
		{
			output.Add(name, value);
		}
	}
	
	void Add(string name, vector value)
	{
		foreach (auto output : m_Outputs)
		{
			output.Add(name, value);
		}
	}
	
	void Add(string name, string value)
	{
		foreach (auto output : m_Outputs)
		{
			output.Add(name, value);
		}
	}
	
	void ResetBuffer()
	{
		foreach (auto output : m_Outputs)
		{
			output.ResetBuffer();
		}
	}

	void PushBuffer()
	{
		foreach (auto output : m_Outputs)
		{
			output.PushBuffer();
		}
	}

	void IncrementTab()
	{
		foreach (auto output : m_Outputs)
		{
			output.IncrementTab();
		}
	}

	void DecrementTab()
	{
		foreach (auto output : m_Outputs)
		{
			output.DecrementTab();
		}
	}

	void Add(string name, Class value)
	{
		string _value = "" + value;

		Object obj;
		if (Class.CastTo(obj, value))
		{
			_value += "(" + obj.GetNetworkIDString() + ")";
		}

		Add(name, _value);
	}

	/**
	 * @brief Calls the 'CF_DebugUI' method for the target Class, 'CF_DebugUI' must return true.
	 */
	void Add(Class value)
	{
		IncrementTab();

		if (value != m_Instance)
		{
			Add("this", value);
		}

		if (value)
		{
			bool functionCallSuccess = false;
			GetGame().GameScript.CallFunctionParams(value, "CF_OnDebugUpdate", functionCallSuccess, new Param2<CF_Debug, CF_DebugUI_Type>(this, CF_Debug.s_Types));

			if (!functionCallSuccess)
			{
				typename type = value.Type();
				int count = type.GetVariableCount();
				for (int i = 0; i < count; i++)
				{
					string variableName = type.GetVariableName(i);
					typename variableType = type.GetVariableType(i);

					CF_TypeConverter converter = CF_TypeConverters.Create(variableType);
					if (converter.FromTypename(value, i))
					{
						Add(variableName, converter.GetString());
					}
				}
			}
		}

		DecrementTab();
	}

	protected override void OnTick(float dt)
	{
		ResetBuffer();

		Add(m_Instance);

		PushBuffer();
	}

	protected override void OnStart()
	{
		CF_MVVM.NotifyPropertyChanged(this, "m_IsActive");
	}

	protected override void OnStop()
	{
		CF_MVVM.NotifyPropertyChanged(this, "m_IsActive");
	}

	void ShowWindow()
	{
		if (m_UI) return;

		Start();
		
		CF_DebugUI ui = new CF_DebugUI(this, GetName());
		m_UI = ui;
		m_Outputs.Insert(ui);

		CF_MVVM.NotifyPropertyChanged(this, "m_UI");
	}

	void CloseWindow()
	{
		m_Outputs.RemoveItemUnOrdered(m_UI);
		m_UI = null;

		CF_MVVM.NotifyPropertyChanged(this, "m_UI");

		if (m_Outputs.Count() == 0)
		{
			Stop();
		}
	}

	void Event_Start(CF_ModelBase sender, CF_EventArgs args)
	{
		Start();
	}

	void Event_Stop(CF_ModelBase sender, CF_EventArgs args)
	{
		Stop();
	}

	void Event_ShowWindow(CF_ModelBase sender, CF_EventArgs args)
	{
		ShowWindow();
	}

	void Event_CloseWindow(CF_ModelBase sender, CF_EventArgs args)
	{
		CloseWindow();
	}
};
