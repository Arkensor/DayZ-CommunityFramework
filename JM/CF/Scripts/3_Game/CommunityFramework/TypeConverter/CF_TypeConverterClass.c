class CF_TypeConverterClass : CF_TypeConverterT<Class>
{
	override int GetInt()
	{
		return (int) m_Value;		
	}

	override bool GetBool()
	{
		return m_Value != null;
	}

	override float GetFloat()
	{
		return GetInt();
	}

	override string GetString()
	{
		string toStr = "";
		g_Script.CallFunction(m_Value, "ToStr", toStr, null);
		return toStr;
	}
	
	override void SetClass(Class value)
	{
		m_Value = value;
	}
	
	override Class GetClass()
	{
		return m_Value;
	}
};
