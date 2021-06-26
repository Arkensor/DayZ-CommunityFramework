class CF_TypeConverterClass : CF_TypeConverterT<Class>
{
	override string GetString()
	{
		return "" + m_Value;
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