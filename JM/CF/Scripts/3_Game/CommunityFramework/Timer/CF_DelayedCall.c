class CF_DelayedCall : CF_TimerBase
{
	protected Class m_Instance;
	protected string m_Function;
	protected ref CF_Param m_Params;

	protected int m_Delay;
	
	/**
	 * @brief Create a delayed call for an unmanaged instances
	 * 
	 * @param instance The instance that owns the function, this delayed call instance must be strongly referenced within instance.
	 * @param function The function that is called
	 * @param delay The time in milliseconds that will pass until the delayed call is fired.
	 * @param params The static parameters that are passed into the function
	 * 
	 * @note The function passed must have a signature that starts with 'CF_TimerBase,float` and then continues with the matching 'params'.
	 */
	void CF_DelayedCall(Class instance, string function, int delay, CF_Param params = null)
	{
		m_Instance = instance;
		m_Function = function;

		m_Delay = delay;

		SetParams(params);

		Start();
	}

	/**
	 * @param instance The instance that owns the function
	 * @param function The function that is called
	 * @param delay The time in milliseconds that will pass until the delayed call is fired.
	 * @param params The static parameters that are passed into the function
	 * 
	 * @note The function passed must have a signature that starts with 'CF_TimerBase,float` and then continues with the matching 'params'.
	 */
	static CF_DelayedCall Create(Class instance, string function, int delay, CF_Param params = null)
	{
		if (instance == null) return null;

		CF_DelayedCall timer;
		
		Managed managedInstance;
		if (Class.CastTo(managedInstance, instance))
		{
			timer = new CF_ManagedDelayedCall(managedInstance, function, delay, params);
			return timer;
		}

		timer = new CF_DelayedCall(instance, function, delay, params);
		return timer;
	}

	void SetParams(CF_Param params)
	{
		m_Params = params;
		if (!m_Params) m_Params = new CF_TimerParam();
		m_Params.SetTimer(this);
	}
	
	protected override void OnUpdate(float dt)
	{
		m_TimeElapsedMS += dt * 1000.0;
		m_TimeElapsed = m_TimeElapsedMS / 1000.0;

		if (m_TimeElapsedMS >= m_Delay)
		{
			m_DeltaTime = dt;

			OnTick(dt);
			
			Destroy();
		}
	}

	protected override void OnTick(float dt)
	{
		m_Params.SetDelta(dt);
		g_Script.CallFunctionParams(m_Instance, m_Function, NULL, m_Params);
	}
};
