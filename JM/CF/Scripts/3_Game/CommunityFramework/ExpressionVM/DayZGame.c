#ifdef CF_EXPRESSION_TEST
modded class DayZGame
{
	private float m_CF_UpdateTime;
	private int m_CF_Tests;

	override void OnUpdate(bool doSim, float timeslice)
	{
		super.OnUpdate(doSim, timeslice);
		if (!doSim) return;

		m_CF_UpdateTime += timeslice;
		if (m_CF_UpdateTime > 5.0 && m_CF_Tests < 3)
		{
			m_CF_UpdateTime = 0;
			m_CF_Tests++;

			CF_ExpressionTests.PerformSingle("TestPerformance");
		}
	}
};
#endif
