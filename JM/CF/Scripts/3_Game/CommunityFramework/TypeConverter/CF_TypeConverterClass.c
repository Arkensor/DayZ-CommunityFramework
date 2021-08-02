class CF_TypeConverterClass : CF_TypeConverterT<Class>
{
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
