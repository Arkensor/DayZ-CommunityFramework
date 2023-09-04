class CF_ManagedDelayedCall : CF_DelayedCall
{
	Managed m_ManagedInstance;
	
	void CF_ManagedDelayedCall(Class instance, string function, int delay, CF_Param params = null)
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
