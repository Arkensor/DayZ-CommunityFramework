class CF_Timer : CF_TimerBase
{
	protected Managed m_Instance;
	protected string m_Function;
	protected ref CF_TimerParam m_Params;
	
	void CF_Timer()
	{
	}

	/**
	 * @param instance The instance that owns the function
	 * @param function The function that is called
	 * @param interval The time between each function call, in seconds.
	 * @param params The static parameters that are passed into the function
	 * 
	 * @note The function passed must have a signature that starts with 'CF_TimerBase,float` and then continues with the matching 'params'.
	 */
	static CF_TimerBase Create(Managed instance, string function, float interval = 0.0, CF_TimerParam params = null)
	{
		if (instance == null) return null;

		CF_Timer timer = new CF_Timer();
		timer.m_Instance = instance;
		timer.m_Function = function;

		timer.SetParams(params);
		timer.SetInterval(interval);
		timer.Start();

		return timer;
	}

	void SetParams(CF_TimerParam params)
	{
		m_Params = params;
		if (!m_Params) m_Params = new CF_TimerParam();
		m_Params.m_Timer = this;
	}
	
	protected override void OnUpdate(float dt)
	{
		if (!m_Instance)
		{
			Destroy();
			return;
		}
		
		super.OnUpdate(dt);
	}

	protected override void OnTick(float dt)
	{
		if (m_Params) m_Params.m_DeltaTime = dt;
		g_Script.CallFunctionParams(m_Instance, m_Function, NULL, m_Params);
	}
};
