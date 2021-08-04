class CF_TimerBase : Managed
{
	private static int s_Count = 0;
	private static ref CF_TimerBase s_Instances[16384];

	protected int m_Index;

	protected float m_Duration;
	protected float m_Time;
	protected int m_TimeMS;

	protected void CF_TimerBase()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "CF_TimerBase");
		#endif

		s_Instances[s_Count] = this;
		m_Index = s_Count;
		s_Count++;

		OnCreate();
	}

	void ~CF_TimerBase()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "~CF_TimerBase");
		#endif

		OnDestroy();

		s_Count--;
		s_Instances[m_Index] = s_Instances[s_Count];
		s_Instances[s_Count] = null;
	}

	void Stop()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Stop");
		#endif

		delete this;
	}

	void SetDuration(float duration)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "SetDuration", "" + duration);
		#endif

		m_Duration = duration;
		if (m_Duration < 0) m_Duration = 0;
	}

	float GetDuration()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "GetDuration");
		#endif

		return m_Duration;
	}

	int GetTime()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "GetTime");
		#endif

		return m_TimeMS;
	}

	protected void OnCreate()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnCreate");
		#endif

	}

	protected void OnDestroy()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnDestroy");
		#endif

	}

	protected void OnUpdate(float dt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnUpdate", "" + dt);
		#endif

		m_TimeMS += dt * 1000.0;
		m_Time += dt;

		if (m_Time >= m_Duration)
		{
			OnTick(dt);
			m_Time = 0;
		}
	}

	protected void OnTick(float dt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnTick", "" + dt);
		#endif

	}

	static void Update(float dt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(null, "CF_TimerBase::Update");
		#endif

		for (int i = 0; i < s_Count; i++)
		{
			s_Instances[i].OnUpdate(dt);
		}
	}
};
