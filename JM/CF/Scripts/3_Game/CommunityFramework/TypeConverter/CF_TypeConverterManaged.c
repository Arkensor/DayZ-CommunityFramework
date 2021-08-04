class CF_TypeConverterManaged : CF_TypeConverterT<Managed>
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
	
	override void SetManaged(Managed value)
	{
		m_Value = value;
	}
	
	override Managed GetManaged()
	{
		return m_Value;
	}
};
