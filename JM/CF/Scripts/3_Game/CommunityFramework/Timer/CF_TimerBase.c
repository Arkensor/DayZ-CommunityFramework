class CF_TimerBase : Managed
{
	protected static ref CF_TimerBase s_Head = new CF_TimerBaseRoot();
	protected static CF_TimerBase s_Tail;

	private ref CF_TimerBase m_Next;
	private CF_TimerBase m_Prev;
	private bool m_IsActive;
	private bool m_Destroy;

	//! It is recommended to not modify these variables while the timer is active/running.
	float m_Interval; // Seconds
	float m_DeltaTime; // Seconds
	float m_TimeElapsed; // Seconds
	int m_TimeElapsedMS; // Milliseconds

	protected void CF_TimerBase()
	{
		DumpStack();
		
		OnCreate();
	}

	void ~CF_TimerBase()
	{
		//Stop();

		OnDestroy();
	}

	void Start()
	{
		if (m_IsActive) return;

		m_IsActive = true;

		m_Prev = s_Tail;
		m_Prev.m_Next = this;

		s_Tail = this;

		OnStart();
	}

	/**
	 * Stops the timer, decrementing the reference count.
	 */
	void Stop()
	{
		if (!m_IsActive) return;

		m_IsActive = false;

		if (this == s_Tail)
		{
			s_Tail = m_Prev;
			if (s_Tail) s_Tail.m_Next = null;
		}
		else
		{
			if (m_Prev) m_Prev.m_Next = m_Next;
			if (m_Next) m_Next.m_Prev = m_Prev;

			m_Next = null;
			m_Prev = null;
		}

		OnStop();
	}

	bool IsActive()
	{
		return m_IsActive;
	}

	bool IsDestroyed()
	{
		return m_Destroy;
	}

	void Destroy()
	{
		m_Destroy = true;
	}

	/**
	 * The time between each 'OnTick' call, in seconds.
	 */
	void SetInterval(float interval)
	{
		m_Interval = interval;
		if (m_Interval < 0) m_Interval = 0;
	}

	/**
	 * The time between each 'OnTick' call, in seconds.
	 */
	float GetInterval()
	{
		return m_Interval;
	}

	/**
	 * The total time elapsed for this timer, in milliseconds.
	 */
	void SetTimeElapsedMS(int elapsed)
	{
		m_TimeElapsedMS = elapsed;
	}

	/**
	 * The total time elapsed for this timer, in milliseconds.
	 */
	int GetTimeElapsedMS()
	{
		return m_TimeElapsedMS;
	}

	/**
	 * The total time elapsed for this timer, in seconds.
	 */
	float GetTimeElapsed()
	{
		return m_TimeElapsed;
	}

	protected void OnCreate();

	protected void OnDestroy();

	protected void OnStart();

	protected void OnStop();

	protected void OnTick(float dt);

	protected void OnUpdate(float dt)
	{
		m_TimeElapsedMS += dt * 1000.0;
		m_TimeElapsed = m_TimeElapsedMS / 1000.0;
		
		m_DeltaTime += dt;

		if (m_DeltaTime < m_Interval)
			return;

		OnTick(m_DeltaTime);
		m_DeltaTime = 0;
	}

	static void _UpdateAll(float dt)
	{
		CF_TimerBase current = s_Head;
		while (current)
		{
			current.OnUpdate(dt);
			if (current.m_Destroy)
				current.Stop();
			
			current = current.m_Next;
		}
	}

	static void _Init()
	{
		s_Tail = s_Head;
		s_Head.m_Next = null;
	}
};

class CF_TimerBaseRoot : CF_TimerBase
{
	void CF_TimerBaseRoot()
	{
		CF_TimerBase.s_Head = this;
		CF_TimerBase.s_Tail = this;
	}

	override void OnUpdate(float dt)
	{
	}
};
