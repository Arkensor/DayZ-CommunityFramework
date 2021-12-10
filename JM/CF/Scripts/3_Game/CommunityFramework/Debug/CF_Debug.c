class CF_Debug : CF_TimerBase
{
	static ref CF_DebugUI_Type s_Types;

	private static ref CF_DebugManager s_Manager;

	[CF_EventSubscriber(CF_Debug._Init, CF_LifecycleEvents.OnGameCreate)]
	static void _Init()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0("CF_Debug", "_Init");
#endif

		s_Types = new CF_DebugUI_Type();
		s_Manager = new CF_DebugManager();

		SetAllowed(false);
	}

	[CF_EventSubscriber(CF_Debug._Cleanup, CF_LifecycleEvents.OnGameDestroy)]
	static void _Cleanup()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0("CF_Debug", "_Cleanup");
#endif

		s_Types = null;
		s_Manager = null;
	}

	[CF_EventSubscriber(CF_Debug._MissionCleanup, CF_LifecycleEvents.OnMissionDestroy)]
	static void _MissionCleanup()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0("CF_Debug", "_MissionCleanup");
#endif

		SetAllowed(false);
	}

	static Widget ShowManager(Widget parent = null)
	{
		return s_Manager.Open(parent);
	}

	static void CloseManager()
	{
		s_Manager.Close();
	}

	static bool IsAllowed()
	{
		return s_Manager.IsAllowed();
	}

	static void SetAllowed(bool newState)
	{
		s_Manager.SetAllowed(newState);
	}

	static void Create(Class instance, string title = "##")
	{
		s_Manager.Create(instance, title);
	}

	static void Destroy(Class instance)
	{
		s_Manager.Destroy(instance);
	}

	protected ref array<ref CF_DebugOutput> m_Outputs = new array<ref CF_DebugOutput>();

	protected Class m_Instance;
	protected string m_Name;
	protected vector m_Position;
	protected bool m_ViewInWorld;
	protected bool m_CanViewInWorld;

	protected Class m_CurrentInstance;

	protected CF_DebugUI m_UI;

	/*private*/ void CF_Debug(Class instance, string name)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "CF_Debug");
#endif

		m_Instance = instance;
		SetName(name);
	}

	void ~CF_Debug()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "~CF_Debug");
#endif
	}

	void SetName(string name)
	{
		m_Name = name;

		foreach (auto output : m_Outputs)
		{
			output.SetName(name);
		}

		CF_MVVM.NotifyPropertyChanged(this, "m_Name");
	}

	string GetName()
	{
		return m_Name;
	}

	/**
	 * @brief Sets the position within the world - always rotated to face the screen
	 * 
	 * @note If attached root instance is an Entity, the position is in model space. Otherwise it is in world space.
	 */
	void SetPosition(vector value)
	{
		if (m_CurrentInstance != m_Instance)
			return;
		
		m_CanViewInWorld = true;

		m_Position = value;
	}

	vector GetPosition()
	{
		return m_Position;
	}
	
	/**
	 * @brief Sets if the window should be viewed within the world
	 */
	void SetViewInWorld(bool viewInWorld)
	{
		m_ViewInWorld = viewInWorld;
	}
	
	/**
	 * @brief Sets if the window can be viewed within the world
	 */
	void SetCanViewInWorld(bool canViewInWorld)
	{
		m_CanViewInWorld = canViewInWorld;
	}
	
	/**
	 * @brief Return if the window can be viewed within the world
	 */
	bool CanViewInWorld()
	{
		return m_CanViewInWorld && m_ViewInWorld;
	}

	/**
	 * @brief Return the owning instance of the debug
	 */
	Class GetInstance()
	{
		return m_Instance;
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

	void Add(string name, int value, typename type)
	{
		Add(name, typename.EnumToString(type, value));
	}

	void Add(string name, int value, array<string> values)
	{
		string vName = "INVALID";
		if (value >= 0 && value < values.Count())
		{
			vName = values[value];
		}

		Add(name, vName);
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
		bool incremented;

		Class previous = m_CurrentInstance;
		m_CurrentInstance = value;

		if (value != m_Instance)
		{
			incremented = true;
			IncrementTab();
			Add("this", value);
		}

		if (value)
		{
			IncrementTab();

			bool functionCallSuccess = false;
			functionCallSuccess = GetGame().GameScript.CallFunctionParams(value, "CF_OnDebugUpdate", functionCallSuccess, new Param2<CF_Debug, CF_DebugUI_Type>(this, CF_Debug.s_Types));

			if (!functionCallSuccess)
			{
				typename type = value.Type();
				int count = type.GetVariableCount();
				for (int i = 0; i < count; i++)
				{
					string variableName = type.GetVariableName(i);
					typename variableType = type.GetVariableType(i);

					CF_TypeConverterBase converter = CF_TypeConverter.Get(variableType);
					if (converter.Read(value, i))
					{
						Add(variableName, converter.GetString());
					}
				}
			}

			DecrementTab();
		}

		if (incremented)
		{
			DecrementTab();
		}
		
		m_CurrentInstance = previous;
	}

	protected override void OnTick(float dt)
	{
		ResetBuffer();

		Add(m_Instance);

		PushBuffer();
	}

	protected override void OnStart()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "OnStart");
#endif

		super.OnStart();

		CF_MVVM.NotifyPropertyChanged(this, "m_IsActive");
	}

	protected override void OnStop()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "OnStop");
#endif

		super.OnStop();

		CF_MVVM.NotifyPropertyChanged(this, "m_IsActive");
	}

	override string GetLayoutFile()
	{
		return "JM/CF/GUI/layouts/debug/entry.layout";
	}

	void ShowWindow()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "ShowWindow");
#endif

		if (m_UI)
		{
			return;
		}

		Start();

		CF_DebugUI ui = new CF_DebugUI(this, GetName());
		m_UI = ui;
		m_Outputs.Insert(ui);

		CF_MVVM.NotifyPropertyChanged(this, "m_UI");
	}

	void CloseWindow()
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "CloseWindow");
#endif

		m_Outputs.RemoveItemUnOrdered(m_UI);
		m_UI = null;

		CF_MVVM.NotifyPropertyChanged(this, "m_UI");

		if (m_Outputs.Count() == 0)
		{
			Stop();
		}
	}

	void Event_ToggleWindow(CF_ModelBase sender, CF_ChangeEventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "Event_ToggleWindow").Add(sender).Add(args);
#endif

		if (m_UI)
		{
			CloseWindow();
		}
		else
		{
			ShowWindow();
		}
	}

	void Event_CloseWindow(CF_ModelBase sender, CF_EventArgs args)
	{
#ifdef CF_TRACE_ENABLED
		auto trace = CF_Trace_0(this, "Event_ToggleWindow").Add(sender).Add(args);
#endif

		CloseWindow();
	}
};
