class CF_TimerBase : TimerBase
{
	static ref array<ref CF_TimerBase> s_GlobalTimers = new array<ref CF_TimerBase>();
	
	protected bool m_IsDestroyed;

	void CF_TimerBase()
	{
		m_duration = 0;
		m_loop = true;
		m_time = 0;
		m_running = false;
		m_timerQueue = g_Game.GetTimerQueue(CALL_CATEGORY_SYSTEM);

		s_GlobalTimers.Insert(this);

		Start();
	}

	void ~CF_TimerBase()
	{
		Destroy();
	}

	protected override void SetRunning(bool running)
	{
		if (m_running == running)
		{
			return;
		}

		super.SetRunning(running);

		if (m_running)
		{
			OnStart();
		}
		else
		{
			OnStop();
		}
	}

	protected override void Tick(float timeslice)
	{
		m_time += timeslice;

		if (m_time >= m_duration)
		{
			OnTick(m_time);

			m_time = 0;
		}
	}

	void Start()
	{
		SetRunning(true);
	}

	void Destroy()
	{
		if (m_IsDestroyed) return;

		m_IsDestroyed = true;

		Stop();

		s_GlobalTimers.RemoveItem(this);
	}

	protected void OnTick(float dt)
	{
	}

	protected void OnStart()
	{
	}

	protected void OnStop()
	{
	}
};
