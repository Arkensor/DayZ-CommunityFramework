class CF_ManagedTimer : CF_TimerBase
{
	Managed m_Instance;
	string m_Function;
	ref CF_TimerParam m_Params;
	
	void CF_ManagedTimer()
	{
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
