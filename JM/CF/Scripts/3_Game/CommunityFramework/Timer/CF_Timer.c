class CF_Timer : CF_TimerBase
{
	protected Managed m_Owner;
	protected string m_Function;

	static CF_Timer Create(Managed instance, string function, float interval = 0.0)
	{
		if (instance == null) return null;

		CF_Timer timer = new CF_Timer();
		timer.m_Owner = instance;
		timer.m_Function = function;
		timer.m_duration = interval;
		
		return timer;
	}

	protected override void OnTick(float dt)
	{
		if (m_Owner == null)
		{
			Destroy();
			return;
		}

		Param params = new Param2<Managed, CF_EventUpdateArgs>(this, new CF_EventUpdateArgs(dt));

		GetGame().GameScript.CallFunctionParams(m_Owner, m_Function, NULL, params);
	}
};
