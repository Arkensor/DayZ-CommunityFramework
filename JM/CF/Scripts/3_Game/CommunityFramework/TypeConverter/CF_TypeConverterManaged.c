class CF_TypeConverterManaged : CF_TypeConverterClass
{
	override string GetString()
	{
		string toStr = "";
		g_Script.CallFunction(m_Value, "ToStr", toStr, null);
		return toStr;
	}
	
	override void SetManaged(Managed value)
	{
		m_Value = value;
	}
	
	override Managed GetManaged()
	{
		return Managed.Cast(m_Value);
	}
};
