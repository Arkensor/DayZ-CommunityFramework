class CF_Timer : CF_TimerBase
{
	Class m_Instance;
	string m_Function;
	ref CF_TimerParam m_Params;
	
	/**
	 * @brief Create a timer for unmanaged instances
	 * 
	 * @param instance The instance that owns the function, this timer instance must be strongly referenced within instance.
	 * @param function The function that is called
	 * @param interval The time between each function call, in seconds.
	 * @param params The static parameters that are passed into the function
	 * 
	 * @note The function passed must have a signature that starts with 'CF_TimerBase,float` and then continues with the matching 'params'.
	 */
	void CF_Timer(Class instance, string function, float interval = 0.0, CF_TimerParam params = null)
	{
		m_Instance = instance;
		m_Function = function;

		SetParams(params);
		SetInterval(interval);

		Start();
	}

	/**
	 * @brief Create a timer 
	 * 
	 * @param instance The instance that owns the function
	 * @param function The function that is called
	 * @param interval The time between each function call, in seconds.
	 * @param params The static parameters that are passed into the function
	 * 
	 * @note If the instance is 'Managed' then the timer does not have to be strongly referenced within the instance.
	 * 
	 * @note The function passed must have a signature that starts with 'CF_TimerBase,float' and then continues with the matching 'params'.
	 */
	static CF_Timer Create(Class instance, string function, float interval = 0.0, CF_TimerParam params = null)
	{
		if (instance == null) return null;

		CF_Timer timer;
		
		Managed managedInstance;
		if (Class.CastTo(managedInstance, instance))
		{
			timer = new CF_ManagedTimer(managedInstance, function, interval, params);
			return timer;
		}

		timer = new CF_Timer(instance, function, interval, params);
		return timer;
	}

	void SetParams(CF_TimerParam params)
	{
		m_Params = params;
		if (!m_Params) m_Params = new CF_TimerParam();
		m_Params.m_Timer = this;
	}

	protected override void OnTick(float dt)
	{
		if (m_Params) m_Params.m_DeltaTime = dt;
		g_Script.CallFunctionParams(m_Instance, m_Function, NULL, m_Params);
	}
};
