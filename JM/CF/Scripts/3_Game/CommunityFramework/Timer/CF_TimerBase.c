class CF_TimerBase : Managed
{
	private static ref CF_TimerBase s_Head;
	private ref CF_TimerBase m_Next;
	private CF_TimerBase m_Prev;
	private bool m_IsActive;
	private bool m_Destroy;

	protected float m_Interval; // Seconds
	protected float m_DeltaTime; // Seconds
	protected int m_Time; // Milliseconds

	protected void CF_TimerBase()
	{
		OnCreate();
	}

	void ~CF_TimerBase()
	{
		Stop();

		OnDestroy();
	}

	void Start()
	{
		if (m_IsActive) return;

		m_IsActive = true;

		if (s_Head == null)
		{
			s_Head = this;
		}
		else
		{
			m_Next = s_Head;
			s_Head.m_Prev = this;
			s_Head = this;
		}

		OnStart();
	}

	/**
	 * Stops the timer, decrementing the reference count.
	 */
	void Stop()
	{
		if (!m_IsActive) return;

		m_IsActive = false;

		if (s_Head == this)
		{
			s_Head = m_Next;
			if (s_Head) s_Head.m_Prev = null;
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
		m_Destroy = true;
	}

	void SetInterval(float duration)
	{
		m_Interval = duration;
		if (m_Interval < 0) m_Interval = 0;
	}

	float GetInterval()
	{
		return m_Interval;
	}

	void SetTime(int time)
	{
		m_Time = time;
	}

	int GetTime()
	{
		return m_Time;
	}

	protected void OnCreate();

	protected void OnDestroy();

	protected void OnStart();

	protected void OnStop();

	protected void OnTick(float dt);

	protected void OnUpdate(float dt)
	{
		m_Time += dt * 1000.0;
		m_DeltaTime += dt;

		if (m_DeltaTime >= m_Interval)
		{
			OnTick(m_DeltaTime);
			m_DeltaTime = 0;
		}
	}

	static void _Update(float dt)
	{
		CF_TimerBase current = s_Head;
		CF_TimerBase next = null;
		while (!current)
		{
			next = current.m_Next;
			current.OnUpdate(dt);
			if (current.m_Destroy) delete current;
			current = next;
		}
	}
};
