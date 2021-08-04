class CF_Timer : CF_TimerBase
{
	protected Managed m_Object;
	protected string m_Function;
	protected ref CF_TimerParam m_Params;
	
	void CF_Timer()
	{
	}

	static CF_TimerBase Create(Managed obj, string funcName, float duration = 0.025, CF_TimerParam params = null)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(null, "Create", "" + obj, "" + funcName, "" + duration, "" + params);
		#endif

		if (obj == null) return null;

		CF_Timer timer = new CF_Timer();
		timer.m_Object = obj;
		timer.m_Function = funcName;
		timer.m_Params = params;
		if (!timer.m_Params) timer.m_Params = new CF_TimerParam();

		timer.SetDuration(duration);

		return timer;
	}
	
	protected override void OnUpdate(float dt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnUpdate", "" + dt);
		#endif

		if (m_Object)
		{
			super.OnUpdate(dt);
			return;
		}
		
		delete this;
	}

	protected override void OnTick(float dt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnTick", "" + dt);
		#endif

		m_Params.m_DeltaTime = dt;
		g_Script.CallFunctionParams(m_Object, m_Function, NULL, m_Params);
	}
};

class CF_TimerParam
{
	CF_Timer m_Timer;
	float m_DeltaTime;
};

class CF_TimerParam1<Class T> : CF_TimerParam
{
	ref T m_Param1;

	void CF_TimerParam1(T param1)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "CF_TimerParam1", "" + param1);
		#endif

		m_Param1 = param1;
	}
};
