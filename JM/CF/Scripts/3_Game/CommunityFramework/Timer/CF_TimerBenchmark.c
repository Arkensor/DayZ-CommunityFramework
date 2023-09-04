//WARNING: DO NOT RUN IN-GAME, THIS WILL BREAK ALL CURRENTLY RUNNING TIMERS
class CF_TimerBenchmark
{
	ref array<ref TimerBase> m_VanillaTimers;

	ref TimerQueue m_TimerQueue;

	static void Run(int num)
	{
		CF_TimerBenchmark benchMark = new CF_TimerBenchmark();
		benchMark.Test(num);
	}

	void CreateTimers(int num, inout int time)
	{
		time = TickCount(0);

		CF_TimerBase._Init();

		m_TimerQueue = new TimerQueue();
		m_VanillaTimers = new array<ref TimerBase>();
		m_VanillaTimers.Resize(num);

		for (int i = 0; i < num; i++)
		{
			new CF_BM_CFTimer();
			m_VanillaTimers.Set(i, new CF_VM_VanillaTimer(0, m_TimerQueue));
		}

		time = TickCount(time);
	}

	void Test(int num)
	{
		int insert = 0;

		CreateTimers(num, insert);

		float insertMS = insert / 10000.0;

		Print("Took " + insert + " ticks for " + num + " timers to be inserted.");
		Print("Took " + insertMS + " ms for " + num + " timers to be inserted.");

		int cf = 0;
		int vanilla = 0;

		TestCF(cf);
		TestVanilla(vanilla);

		float cfMS = cf / 10000.0;
		float vanillaMS = vanilla / 10000.0;

		Print("CF Timer took " + cf + " ticks for " + num + " timers inserted.");
		Print("Vanilla Timer took " + vanilla + " ticks for " + num + " timers inserted.");

		Print("CF Timer took " + cfMS + " ms for " + num + " timers inserted.");
		Print("Vanilla Timer took " + vanillaMS + " ms for " + num + " timers inserted.");

		CF_TimerBase._Init();
	}

	void TestCF(inout int time)
	{
		time = TickCount(0);
		CF_TimerBase._UpdateAll(0.1);
		time = TickCount(time);
	}

	void TestVanilla(inout int time)
	{
		time = TickCount(0);
		m_TimerQueue.Tick(0.1);
		time = TickCount(time);
	}
};

class CF_BM_CFTimer : CF_TimerBase
{
	void CF_BM_CFTimer()
	{
		SetInterval(0.0);
		Start();
	}
};

class CF_VM_VanillaTimer : TimerBase
{
	void CF_VM_VanillaTimer(int category = CALL_CATEGORY_SYSTEM, TimerQueue queue = null)
	{
		m_timerQueue = queue;

		OnStart(0.0, true);
	}

	protected override void OnInit(int category)
	{
		m_duration = 1;
		m_loop = false;
		m_time = 0;
		m_running = false;
	}
};
