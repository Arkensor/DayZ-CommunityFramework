class CF_TimerBase : Managed
{
	private static ref CF_TimerBase s_Root;
	private ref CF_TimerBase m_Next;
	private CF_TimerBase m_Prev;
	private bool m_IsActive;
	private bool m_Destroy;

	protected float m_Interval; // Seconds
	protected float m_DeltaTime; // Seconds
	protected int m_Time; // Milliseconds

	protected void CF_TimerBase()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "CF_TimerBase");
		#endif

		OnCreate();
	}

	void ~CF_TimerBase()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "~CF_TimerBase");
		#endif

		Stop();

		OnDestroy();
	}

	void Start()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Start");
		#endif

		if (m_IsActive) return;

		m_IsActive = true;

		if (s_Root == null)
		{
			s_Root = this;
		}
		else
		{
			m_Next = s_Root;
			s_Root.m_Prev = this;
			s_Root = this;
		}

		OnStart();
	}

	/**
	 * Stops the timer, decrementing the reference count.
	 */
	void Stop()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Stop");
		#endif

		if (!m_IsActive) return;

		m_IsActive = false;

		if (s_Root == this)
		{
			s_Root = m_Next;
			if (s_Root) s_Root.m_Prev = null;
		}
		else
		{
			m_Prev.m_Next = m_Next;
			if (m_Next) m_Next.m_Prev = m_Prev;
		}

		OnStop();
	}

	void Destroy()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "Stop");
		#endif

		m_Destroy = true;
	}

	void SetInterval(float duration)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "SetInterval", "" + duration);
		#endif

		m_Interval = duration;
		if (m_Interval < 0) m_Interval = 0;
	}

	float GetInterval()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "GetInterval");
		#endif

		return m_Interval;
	}

	void SetTime(int time)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "SetTime", "" + time);
		#endif

		m_Time = time;
	}

	int GetTime()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "GetTime");
		#endif

		return m_Time;
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

	protected void OnStart()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnStart");
		#endif

	}

	protected void OnStop()
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnStop");
		#endif

	}

	protected void OnTick(float dt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnTick", "" + dt);
		#endif

	}

	protected void OnUpdate(float dt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(this, "OnUpdate", "" + dt);
		#endif

		m_Time += dt * 1000.0;
		m_DeltaTime += dt;

		if (m_DeltaTime >= m_Interval)
		{
			OnTick(m_DeltaTime);
			m_DeltaTime = 0;
		}
	}

	static void Update(float dt)
	{
		#ifdef CF_TRACE_ENABLED
		CF_Trace trace(null, "CF_TimerBase::Update");
		#endif

		CF_TimerBase current = s_Root;
		CF_TimerBase next = null;
		while (current != null)
		{
			next = current.m_Next;
			current.OnUpdate(dt);
			if (current.m_Destroy) delete current;
			current = next;
		}
	}
};
