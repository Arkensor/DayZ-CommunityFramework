//TODO: Add `CF_Param` as a base Param class, will return a `CF_TypeConverter` for each possible param
class CF_Param
{
	void SetTimer(CF_TimerBase timer);
	void SetDelta(float dt);
};

class CF_TimerParam : CF_Param
{
	CF_TimerBase m_Timer;
	float m_DeltaTime;

	override void SetTimer(CF_TimerBase timer)
	{
		m_Timer = timer;
	}

	override void SetDelta(float dt)
	{
		m_DeltaTime = dt;
	}
};

class CF_TimerParam1<Class T1> : CF_TimerParam
{
	T1 m_Param1;

	void CF_TimerParam1(T1 param1)
	{
		m_Param1 = param1;
	}
};

class CF_TimerParam2<Class T1, Class T2> : CF_TimerParam
{
	T1 m_Param1;
	T2 m_Param2;

	void CF_TimerParam2(T1 param1, T2 param2)
	{
		m_Param1 = param1;
		m_Param2 = param2;
	}
};

class CF_TimerParam3<Class T1, Class T2, Class T3> : CF_TimerParam
{
	T1 m_Param1;
	T2 m_Param2;
	T3 m_Param3;

	void CF_TimerParam3(T1 param1, T2 param2, T3 param3)
	{
		m_Param1 = param1;
		m_Param2 = param2;
		m_Param3 = param3;
	}
};

class CF_TimerParam4<Class T1, Class T2, Class T3, Class T4> : CF_TimerParam
{
	T1 m_Param1;
	T2 m_Param2;
	T3 m_Param3;
	T4 m_Param4;

	void CF_TimerParam4(T1 param1, T2 param2, T3 param3, T4 param4)
	{
		m_Param1 = param1;
		m_Param2 = param2;
		m_Param3 = param3;
		m_Param4 = param4;
	}
};

class CF_TimerParam5<Class T1, Class T2, Class T3, Class T4, Class T5> : CF_TimerParam
{
	T1 m_Param1;
	T2 m_Param2;
	T3 m_Param3;
	T4 m_Param4;
	T5 m_Param5;

	void CF_TimerParam5(T1 param1, T2 param2, T3 param3, T4 param4, T5 param5)
	{
		m_Param1 = param1;
		m_Param2 = param2;
		m_Param3 = param3;
		m_Param4 = param4;
		m_Param5 = param5;
	}
};

class CF_TimerParam6<Class T1, Class T2, Class T3, Class T4, Class T5, Class T6> : CF_TimerParam
{
	T1 m_Param1;
	T2 m_Param2;
	T3 m_Param3;
	T4 m_Param4;
	T5 m_Param5;
	T6 m_Param6;

	void CF_TimerParam6(T1 param1, T2 param2, T3 param3, T4 param4, T5 param5, T6 param6)
	{
		m_Param1 = param1;
		m_Param2 = param2;
		m_Param3 = param3;
		m_Param4 = param4;
		m_Param5 = param5;
		m_Param6 = param6;
	}
};

class CF_TimerParam7<Class T1, Class T2, Class T3, Class T4, Class T5, Class T6, Class T7> : CF_TimerParam
{
	T1 m_Param1;
	T2 m_Param2;
	T3 m_Param3;
	T4 m_Param4;
	T5 m_Param5;
	T6 m_Param6;
	T7 m_Param7;

	void CF_TimerParam7(T1 param1, T2 param2, T3 param3, T4 param4, T5 param5, T6 param6, T7 param7)
	{
		m_Param1 = param1;
		m_Param2 = param2;
		m_Param3 = param3;
		m_Param4 = param4;
		m_Param5 = param5;
		m_Param6 = param6;
		m_Param7 = param7;
	}
};

class CF_TimerParam8<Class T1, Class T2, Class T3, Class T4, Class T5, Class T6, Class T7, Class T8> : CF_TimerParam
{
	T1 m_Param1;
	T2 m_Param2;
	T3 m_Param3;
	T4 m_Param4;
	T5 m_Param5;
	T6 m_Param6;
	T7 m_Param7;
	T8 m_Param8;

	void CF_TimerParam8(T1 param1, T2 param2, T3 param3, T4 param4, T5 param5, T6 param6, T7 param7, T8 param8)
	{
		m_Param1 = param1;
		m_Param2 = param2;
		m_Param3 = param3;
		m_Param4 = param4;
		m_Param5 = param5;
		m_Param6 = param6;
		m_Param7 = param7;
		m_Param8 = param8;
	}
};

class CF_TimerParam9<Class T1, Class T2, Class T3, Class T4, Class T5, Class T6, Class T7, Class T8, Class T9> : CF_TimerParam
{
	T1 m_Param1;
	T2 m_Param2;
	T3 m_Param3;
	T4 m_Param4;
	T5 m_Param5;
	T6 m_Param6;
	T7 m_Param7;
	T8 m_Param8;
	T9 m_Param9;

	void CF_TimerParam9(T1 param1, T2 param2, T3 param3, T4 param4, T5 param5, T6 param6, T7 param7, T8 param8, T9 param9)
	{
		m_Param1 = param1;
		m_Param2 = param2;
		m_Param3 = param3;
		m_Param4 = param4;
		m_Param5 = param5;
		m_Param6 = param6;
		m_Param7 = param7;
		m_Param8 = param8;
		m_Param9 = param9;
	}
};
