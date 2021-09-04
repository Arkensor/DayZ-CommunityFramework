class CF_ManagedTimer : CF_Timer
{
	Managed m_ManagedInstance;
	
	void CF_ManagedTimer(Class instance, string function, float interval = 0.0, CF_Param params = null)
	{
		Class.CastTo(m_ManagedInstance, instance);
	}
	
	protected override void OnUpdate(float dt)
	{
		if (!m_ManagedInstance)
		{
			Destroy();
			return;
		}
		
		super.OnUpdate(dt);
	}
};
